
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>

#define N 50000

double maxp, maxf = 0;
int x_maxp, y_maxp, x_maxf, y_maxf;
struct result{
    double max;
    int x, y;
};

double f(int x, int y)
{
    return x * x * x * sin((double)x) - y * y * y * cos((double)y) + x * y * y;
}
int tube[3][2];

int main(void)
{
    // creation du tube
    for (int i = 0; i < 3; i++) {
        if (pipe(tube[i]) == -1) {
            perror("pipe");
            exit(1);
        }
    }
    
    // creation des 3 fils
    for (int p = 1; p <= 3; p++) {
        int k = fork();
        if (k == 0) { // code fils
            close(tube[p-1][0]); // ferme lecture

            struct result res = {0, 0, 0};
            for (int x = p; x <= N; x += 4) {
                for (int y = 0; y <= N; y++) {
                    double val = f(x,y);
                    if (fabs(val) > res.max) {
                        res.max = val;
                        res.x = x;
                        res.y = y;
                    }
                }
            }

            // envoi résultat au père
            write(tube[p-1][1], &res, sizeof(res));
            close(tube[p-1][1]);
            printf("fin fils %d\n", p);
            exit(0);
        }
    }
    // ---- père ----
    struct result best = {0,0,0};

    for (int x = 0; x <= N; x += 4) {
        for (int y = 0; y <= N; y++) {
            double val = f(x,y);
            if (fabs(val) > best.max) {
                best.max = val;
                best.x = x;
                best.y = y;
            }
        }
    }

    // attente des fils et lecture de leurs résultats
    for (int p = 1; p <= 3; p++) {
        wait(NULL);
        struct result res;
        read(tube[p-1][0], &res, sizeof(res));
        close(tube[p-1][0]);
        if (res.max > best.max) {
            best = res;
        }
    }

    if (best.max > 0) {
        printf("le max est atteint en (x=%d, y=%d) et vaut %f\n", best.x, best.y, best.max);
    } else {
        printf("aucun max trouve\n");
    }

    return 0;
}