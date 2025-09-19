#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include "td_1_calcul.h"

#define N 50000

int K;
double *tab_max;
int *tab_x;
int *tab_y;

int **tube;

void init(){
    printf("Entrez le nombre de processus (K>=1) : ");
    scanf("%d", &K);

    // calloc ou malloc
    tab_max = (double *)calloc(K, sizeof(double));
    tab_x   = (int *)calloc(K, sizeof(int));
    tab_y   = (int *)calloc(K, sizeof(int));

    tube = (int **)calloc(K, sizeof(int *));
    for (int i = 0; i < K; i++) {
        tube[i] = calloc(2, sizeof(int));
    }
}

int main(void){
    init();
    for (int i = 0; i < K; i++) {
        pipe(tube[i]);
        int k = fork();
        if (k > 0) { // code père
            close(tube[i][1]);
        }
        else { // code fils
            printf("fils %d créé\n", i);
            close(tube[i][0]); // ferme lecture

            for (int x = i; x <= N; x += K) {
                for (int y = 0; y <= N; y++) {
                    float val = f(x,y);
                    if (fabs(val) > tab_max[i]) {
                        tab_max[i] = val;
                        tab_x[i] = x;
                        tab_y[i] = y;
                    }
                }
            }

            write(tube[i][1], &tab_max[i], sizeof(tab_max[i]));
            write(tube[i][1], &tab_x[i], sizeof(tab_x[i]));
            write(tube[i][1], &tab_y[i], sizeof(tab_y[i]));
            close(tube[i][1]);
            printf("fin fils %d\n", i);
            exit(0);
        }
    }

    double max = 0;
    int x_max = 0;
    int y_max = 0;

    for (int p = 0; p < K; p++) {
        double tmp_max;
        int tmp_x, tmp_y;

        read(tube[p][0], &tmp_max, sizeof(tmp_max));
        read(tube[p][0], &tmp_x, sizeof(tmp_x));
        read(tube[p][0], &tmp_y, sizeof(tmp_y));

        if (tmp_max > max) {
            max = tmp_max;
            x_max = tmp_x;
            y_max = tmp_y;
        }
    }

    for (int p = 0; p < K; p++) {
        wait(NULL);
    }
    printf("Le max est atteint en (x=%d, y=%d) et vaut %f\n", x_max, y_max, max);

    free(tab_max);
    free(tab_x);
    free(tab_y);
    for (int i = 0; i < K; i++) {
        free(tube[i]);
    }
    free(tube);
}
