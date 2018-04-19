#include "fib.h"

int fib(int n)
{
    if (n < 2)
        return n;

    int x;
    int y;

    const int tune = 40;

#pragma omp task firstprivate(n) shared(x)
    {
        x = fib(n-1);
    }
#pragma omp task firstprivate(n) shared(y)
    {
       y = fib(n-2);
    }
#pragma omp taskwait

    return x + y;
}

