#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>

#include "td_1_calcul.h" 

#define N 75000
int K;

typedef struct {
    int i;          // Indice du thread
    double *tab_max;
    int *tab_x;
    int *tab_y;
} thread_args;

// Fonction exécutée par chaque thread
void *calcul(void *arg) {
    thread_args *args = (thread_args *)arg;
    int i = args->i;

    for (int x = i; x <= N; x += K) {
        for (int y = 0; y <= N; y++) {
            float cal = f(x, y);
            if (fabs(cal) > args->tab_max[i]) {
                args->tab_max[i] = cal;
                args->tab_x[i] = x;
                args->tab_y[i] = y;
            }
        }
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Il faut un paramètre : le nombre de threads\n");
        return 1;
    }
    if (sscanf(argv[1], "%d", &K) < 1) {
        printf("Il faut un entier\n");
        return 1;
    }

    // Allocation des tableaux pour stocker les résultats de chaque thread
    double *tab_max = (double *)calloc(K, sizeof(double));
    int *tab_x = (int *)calloc(K, sizeof(int));
    int *tab_y = (int *)calloc(K, sizeof(int));

    pthread_t *tid = malloc(K * sizeof(pthread_t));
    thread_args *args = malloc(K * sizeof(thread_args));

    // Création des threads
    for (int i = 0; i < K; i++) {
        args[i].i = i;
        args[i].tab_max = tab_max;
        args[i].tab_x = tab_x;
        args[i].tab_y = tab_y;
        pthread_create(&tid[i], NULL, calcul, &args[i]);
    }

    // Attente de la fin des threads
    for (int i = 0; i < K; i++) {
        pthread_join(tid[i], NULL);
    }

    // Calcul du maximum global
    double max = 0;
    int x = 0, y = 0;
    for (int i = 0; i < K; i++) {
        if (tab_max[i] > max) {
            max = tab_max[i];
            x = tab_x[i];
            y = tab_y[i];
        }
    }

    printf("Le max est atteint en (x=%d, y=%d) et vaut %.2f\n", x, y, max);

    free(tab_max);
    free(tab_x);
    free(tab_y);
    free(tid);
    free(args);

    return 0;
}
