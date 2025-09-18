
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "td_1_calcul.h"

#define N 50000

double maxp, maxf = 0;
int x_maxp, y_maxp, x_maxf, y_maxf;

int main(void)
{
    int k = fork();
    if (k > 0)
    {
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
    }
    else
    {
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
        exit(0);
    }
    if (maxp > maxf)
        printf("pere %f, fils %f: le max est atteint en (x=%d, y=%d) et vaut %f\n", maxp, maxf, x_maxp, y_maxp, maxp);
    else
        printf("fils %f, pere %f: le max est atteint en (x=%d, y=%d) et vaut %f\n", maxf, maxp, x_maxf, y_maxf, maxf);
}