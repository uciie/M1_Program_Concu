#include "td_1_calcul.h"
#include <math.h>

double f(int x, int y)
{
    return x * x * x * sin((double)x) - y * y * y * cos((double)y) + x * y * y;
}