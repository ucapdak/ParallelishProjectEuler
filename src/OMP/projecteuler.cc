#include "projecteuler.h"

int ProblemOne()
{
    int globalSum = 0;

#pragma omp parallel
    {
        int localSum = 0;

#pragma omp for 
        for (int i = 1; i < 1000; i++)
        {
            if (i % 3 == 0 || i % 5 == 0)
                localSum += i;
        }

#pragma omp atomic
        globalSum += localSum;

    }

    return globalSum;
}
int ProblemTwo()
{
    int evenFib = 2;

    int fib1 = 1;
    int fib2 = 2;
    int temp = 0;

    while (fib2 < 4000000)
    {
        temp = fib2;
        fib2 += fib1;

        if (fib2 % 2 == 0)
            evenFib += fib2;

        fib1 = temp;
    }

    return evenFib;
}