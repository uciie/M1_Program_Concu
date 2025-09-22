
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <sys/wait.h>

#include "td_1_calcul.h"

#define N 75000
int K;
double *tab_max;
int *tab_x;
int *tab_y;

int **tube; // int tube[K][2]

void init(int argn, char *argv[])
{
    if (argn <2){
        printf("il faut un parametre : le nombre de processus\n");
        exit(1);
    }
    if (sscanf(argv[1], "%d", &K)<1){
        printf("Il faut un entier\n");
        exit(1);
    };
    tab_max = (double *)calloc(K, sizeof(double));
    tab_x = (int *)calloc(K, sizeof(int));
    tab_y = (int *)calloc(K, sizeof(int));

    tube = calloc(K, sizeof(int *));
    for (int i = 0; i < K; tube[i++] = (int *)calloc(2, sizeof(int)))
        ;
}
int main(int argn, char *argv[])
{
    init(argn, argv);
    for (int i = 0; i < K; i++)
    {
        pipe(tube[i]);
        int k = fork();
        if (k > 0)
        {
            close(tube[i][1]);
        }
        else
        {
            //printf("demarrage du fils %d\n", i);
            close(tube[i][0]);
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
            write(tube[i][1], &tab_max[i], sizeof(tab_max[i]));
            write(tube[i][1], &tab_x[i], sizeof(tab_x[i]));
            write(tube[i][1], &tab_y[i], sizeof(tab_y[i]));
            //printf("fin du fils %d, max = %.2f pour x=%d\n", i, tab_max[i], tab_x[i]);
            close(tube[i][1]);
            exit(0);
        }
    }

    double max = 0;
    int x, y;
    for (int i = 0; i < K; i++)
    {
        read(tube[i][0], &max, sizeof(max));
        read(tube[i][0], &x, sizeof(x));
        read(tube[i][0], &y, sizeof(y));
    }
    for (int i = 0; i < K; i++)
    {
        wait(NULL);
        close(tube[i][0]);
    }
    //printf("calcul du max\n");
    for (int i = 0; i < K; i++){
        if (tab_max[i]> max){
            max = tab_max[i];
            x = tab_x[i];
            y = tab_y[i];
        }
    }
    printf("le max est atteint en (x=%d, y=%d) et vaut %.2f\n", x, y, max);
}