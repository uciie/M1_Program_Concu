
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "td_1_calcul.h"

#define N 50000

double maxp, maxf = 0;
int x_maxp, y_maxp, x_maxf, y_maxf;

struct result{
    double max;
    int x, y;
};


int main(void)
{
    // creation du tube
    int tube[2];
    pipe(tube);

    int k = fork();
    if (k > 0)
    {
        close(tube[1]); // on ferme l'ecriture du tube
        for (int x = 0; x <= N; x += 2)
        {
            for (int y = 0; y <= N; y++)
            {
                float cal = f(x, y);
                if (fabs(cal) > maxp)
                {
                    maxp = cal;
                    x_maxp = x;
                    y_maxp = y;
                }
            }
        }
        wait(NULL);
        printf("fin pere\n");

        // lecture du tube fils
        struct result resf = {maxf, x_maxf, y_maxf};
        read(tube[0], &resf, sizeof(resf));
        close(tube[0]); // on ferme la lecture du tube

        // comparer
        if (maxp > resf.max)
            printf("le max est atteint en (x=%d, y=%d) et vaut %.1f (père)\n", x_maxp, y_maxp, maxp);
        else
            printf("le max est atteint en (x=%d, y=%d) et vaut %.1f (fils)\n", resf.x, resf.y, resf.max);
    }
    else
    {
        close(tube[0]); // on ferme la lecture du tube
        for (int x = 1; x <= N; x += 2)
        {
            for (int y = 0; y <= N; y++)
            {
                float cal = f(x, y);
                if (fabs(cal) > maxf)
                {
                    maxf = cal;
                    x_maxf = x;
                    y_maxf = y;
                }
            }
        }
        printf("fin fils\n");

        // ecriture dans le tube
        struct result resf;
        resf.max = maxf;
        resf.x = x_maxf;
        resf.y = y_maxf;
        write(tube[1], &resf, sizeof(resf));
        close(tube[1]); // on ferme l'ecriture du tube

        exit(0);
    }
    
}