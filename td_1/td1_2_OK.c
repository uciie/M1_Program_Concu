
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

double f(int x, int y)
{
    return x * x * x * sin((double)x) - y * y * y * cos((double)y) + x * y * y;
}
int tube[2];

int main(void)
{
    pipe(tube);
    int k = fork();
    if (k > 0)
    {
        close(tube[1]);
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
        read(tube[0], &maxf, sizeof(maxf));
        read(tube[0], &x_maxf, sizeof(x_maxf));
        read(tube[0], &y_maxf, sizeof(y_maxf));
        wait(NULL);
        printf("fin pere\n");
    }
    else
    {
        close(tube[0]);
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
        write(tube[1], &maxf, sizeof(maxf));
        write(tube[1], &x_maxf, sizeof(x_maxf));
        write(tube[1], &y_maxf, sizeof(y_maxf));
        exit(0);
    }
    if (maxp > maxf)
        printf("pere %f, fils %f: le max est atteint en (x=%d, y=%d) et vaut %f\n", maxp, maxf, x_maxp, y_maxp, maxp);
    else
        printf("fils %f, pere %f: le max est atteint en (x=%d, y=%d) et vaut %f\n", maxf, maxp, x_maxf, y_maxf, maxf);

}