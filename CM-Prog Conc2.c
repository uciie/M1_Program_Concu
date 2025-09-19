#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define N 10

void *affCar(void *arg){
    char c;
    c = * (char *)arg;
    while(1){
        putchar(c);
    }
}

void *affCar2(void *arg){
    char c;int i;
    c = * (char *)arg;
    for (i=0; i<N; i++){
        putchar( c );
    }
}

pthread_t cree_tache(void * (*start_routine)(void *), void * arg){
    pthread_t id;
    int erreur;
    erreur = pthread_create( &id, NULL, start_routine, arg);
    if (erreur != 0){
    perror( "Echec creation de tâche Posix" );
    exit(-1);
    }
    return id;
}

int main1(void){
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

int main2(void){
    // Problème : les deux tâches affichent le même caractère, la memoire est partagée
    // pour regler le problème il faut un sleep entre les deux créations de tâches
    char leCar;
    
    pthread_t tache_Posix_B;
    pthread_t tache_Posix_C;
    
    leCar = 'B';
    pthread_create( &tache_Posix_B, NULL, affCar, (void*) &leCar);
    
    // sleep(1); // pour régler le problème

    leCar = 'C';
    pthread_create( &tache_Posix_C, NULL, affCar, (void*) &leCar);
    
    while(1){
        putchar('Z');
    }
    
    return 0;
}

int main3(void){
    // Problème : on gere mal la terminaison des tâches
    // pour regler le problème il faut utiliser pthread_join
    
    char *leCar; int i;
    pthread_t tache_Posix_B;
    pthread_t tache_Posix_C;
    
    leCar = (char*) malloc(1*sizeof(char)); *leCar = 'B';
    tache_Posix_B = cree_tache( affCar2, (void*) leCar);
    
    leCar = (char*) malloc(1*sizeof(char)); *leCar = 'C';
    tache_Posix_C = cree_tache( affCar2, (void*) leCar);
    
    for (i=0; i<N; i++){
        putchar('Z');
    }
    putchar('\n');
    
    return 0;
}

int main4(void){
    char *leCar; int i;
    
    pthread_t tache_Posix_B;
    pthread_t tache_Posix_C;
    
    leCar = (char*) malloc(1*sizeof(char)); *leCar = 'B';
    tache_Posix_B = cree_tache( affCar2, (void*) leCar);
    
    leCar = (char*) malloc(1*sizeof(char)); *leCar = 'C';
    tache_Posix_C = cree_tache( affCar2, (void*) leCar);
    
    for (i=0; i<N; i++){
        putchar('Z');
    }
    // Attente de la terminaison des fils avant de terminer le père
    pthread_join( tache_Posix_B, NULL);
    pthread_join( tache_Posix_C, NULL);

    putchar('\n');
    return 0;
}

int main5(void){
    // On force l'ordre d'exécution des tâches
    char *leCar; int i;
    
    pthread_t tache_Posix_B;
    pthread_t tache_Posix_C;
    
    leCar = (char*) malloc(1*sizeof(char)); *leCar = 'B';
    tache_Posix_B = cree_tache( affCar2, (void*) leCar);
    pthread_join( tache_Posix_B, NULL);
    
    leCar = (char*) malloc(1*sizeof(char)); *leCar = 'C';
    tache_Posix_C = cree_tache( affCar2, (void*) leCar);
    pthread_join( tache_Posix_C, NULL);

    for (i=0; i<N; i++){
        putchar('Z');
    }

    putchar('\n');
    return 0;
}

int main(void){
    // return main1();
    // return main2();
    // return main3();
    // return main4();
     return main5();
}