#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define MAX 100

int NbRessDispo = MAX;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void request(int m){
    while(m > NbRessDispo){
        pthread_mutex_lock(&mutex);
        NbRessDispo -= m;
        pthread_mutex_unlock(&mutex);
    }
}


void release(int m){
    pthread_mutex_lock(&mutex);
    NbRessDispo += m;
    pthread_mutex_unlock(&mutex);
}

void tache(){
    while(1){
        int m = rand() % 10;
        request(m);
        sleep(1);
        release(m);
    }
}

int main(int argc, char* argv[]){
    pthread_t t1, t2;
    pthread_create(&t1, NULL, (void *) tache, NULL);
    pthread_create(&t2, NULL, (void *) tache, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&mutex);
    return EXIT_SUCCESS;
}

