#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define N 100000

int Val = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void Inc(void){
    for (int i=0; i<N; i++){
        Val++;
    }
}

void Dec(void){
    for (int i=0; i<N; i++){
        Val--;
    }
}

void IncProtect(void){
    for (int i=0; i<N; i++){
        pthread_mutex_lock(&mutex);
        Val++;
        pthread_mutex_unlock(&mutex);
    }
}

void DecProtect(void){
    for (int i=0; i<N; i++){
        pthread_mutex_lock(&mutex);
        Val--;
        pthread_mutex_unlock(&mutex);
    }
}

int main(void){
    pthread_t t1, t2;
    pthread_create( &t1, NULL, (void *) Inc, NULL);
    pthread_create( &t2, NULL, (void *) Dec, NULL);
    pthread_join( t1, NULL);
    pthread_join( t2, NULL);
    printf("Val=%d\n", Val);

    /* Utilisation du mutex */
    Val = 0;
    pthread_create( &t1, NULL, (void *) IncProtect, NULL);
    pthread_create( &t2, NULL, (void *) DecProtect, NULL);
    pthread_join( t1, NULL);
    pthread_join( t2, NULL);
    printf("Val=%d\n", Val);
    pthread_mutex_destroy(&mutex);
    return 0;
}
