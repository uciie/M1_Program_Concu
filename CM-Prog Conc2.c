#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *affCar(void *arg){
    char c;
    c = * (char *)arg;
    while(1){
        putchar(c);
    }
}

int main(void){
    char *leCar;
    
    pthread_t tache_Posix_B;
    pthread_t tache_Posix_C;

    leCar = (char*) malloc(1*sizeof(char)); *leCar = 'B';
    pthread_create( &tache_Posix_B, NULL, affCar, (void*) leCar);
    
    leCar = (char*) malloc(1*sizeof(char)); *leCar = 'C';
    pthread_create( &tache_Posix_C, NULL, affCar, (void*) leCar);
    
    while(1){
        putchar('Z');
    }
    return 0;
}