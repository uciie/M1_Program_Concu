
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>

#include "td_1_calcul.h"

#define N 75000
int K;
double *tab_max;
int *tab_x;
int *tab_y;

pthread_t *tab_ID;

void init(int argn, char *argv[])
{
    if (argn < 2)
    {
        printf("il faut un parametre : le nombre de processus\n");
        exit(1);
    }
    if (sscanf(argv[1], "%d", &K) < 1)
    {
        printf("Il faut un entier\n");
        exit(1);
    };
    tab_max = (double *)calloc(K, sizeof(double));
    tab_x = (int *)calloc(K, sizeof(int));
    tab_y = (int *)calloc(K, sizeof(int));
    tab_ID = (pthread_t *)calloc(K, sizeof(pthread_t));
}

void *code_thread(void *arg)
{
    int i;
    i = *(int *)arg;
    printf("demmarage de la thread %d\n", i);
    for (int x = i; x <= N; x += K)
    {
        for (int y = 0; y <= N; y++)
        {
            float cal = f(x, y);
            if (fabs(cal) > tab_max[i])
            {
                tab_max[i] = cal;
                tab_x[i] = x;
                tab_y[i] = y;
            }
        }
    }
    return(NULL);
}
int main(int argn, char *argv[])
{
    init(argn, argv);
    for (int i = 0; i < K; i++)
    {
        int *v = malloc(sizeof(int));
        *v = i;
        pthread_create(&tab_ID[i], NULL, code_thread, (void *)v);
    }

    // on attend la fin des thread fils
    for (int i = 0; i < K; i++)
    {
        pthread_join(tab_ID[i], NULL);
    }
    double max = 0;
    int x, y;

    // printf("calcul du max\n");
    for (int i = 0; i < K; i++)
    {
        if (tab_max[i] > max)
        {
            max = tab_max[i];
            x = tab_x[i];
            y = tab_y[i];
        }
    }
    printf("le max est atteint en (x=%d, y=%d) et vaut %.2f\n", x, y, max);
}