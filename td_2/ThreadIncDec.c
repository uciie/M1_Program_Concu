#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>

#define N 10000

void *inc_thread(void *arg){
    int *x;
    x = (int *)arg;
    for (int i=0; i<N; i++){
        //printf("x=%d\t+\n", *x);
        (*x)++;
        
    }
    return(NULL);
}

void *dec_thread(void *arg){
    int *x;
    x = (int *)arg;
    for (int i=0; i<N; i++){
        //printf("x=%d\t-\n", *x);
        (*x)--;
    }
    return(NULL);
}

int main(void){
    int x=0;
    pthread_t t1, t2;
    pthread_create( &t1, NULL, inc_thread, (void*) &x);
    pthread_join( t1, NULL);
    pthread_create( &t2, NULL, dec_thread, (void*) &x);
    pthread_join( t2, NULL);
    printf("x=%d\n", x);
    return 0;
}