#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
//#include <sys/wait.h>

#include "td_1_calcul.h"
#define N 50000

float max = 0;
int x_max, y_max;

int main(void)
{

    for (int x = 0; x <= N; x++)
    {
        for (int y = 0; y <= N; y++)
        {
            float cal = f(x, y);
            if (fabs(cal) > max)
            {
                max = cal;
                x_max = x;
                y_max = y;
            }
        }
    }
    printf("le max est atteint en (x=%d, y=%d) et vaut %.1f\n", x_max, y_max, max);
}