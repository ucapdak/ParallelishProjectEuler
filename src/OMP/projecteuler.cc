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
