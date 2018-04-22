#include "projecteuler.h"

int ReverseNumber(int n)
{
    std::ostringstream convert;
    convert << n;
    std::string str = convert.str();
    std::reverse(str.begin(),str.end());

    std::istringstream buffer(str);
    int reversed;
    buffer >> reversed;

    return reversed;
}
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
int ProblemThree()
{
    long largeNumber = 600851475143;
    long upperBound = (long) std::sqrt(largeNumber);
    long largestFactor = 0;

    std::vector<int> sieve(upperBound, 1);

#pragma omp parallel
#pragma omp for 
    for (long i = 2; i < upperBound; i++)
        if (sieve[i])
            for (long j = i + i; j < upperBound; j += i)
                sieve[j] = 0;

    for (largestFactor = upperBound; largestFactor > 0; largestFactor--)
        if (sieve[largestFactor] && largeNumber % largestFactor == 0)
            break;

    return largestFactor;
}
int ProblemFour()
{
    int greatestProduct = 0;

#pragma omp parallel
    {
        int product;

#pragma omp for 
        for (int i = 100; i < 1000; i++)
        {
            for (int j = i; j < 1000; j++)
            {
                product = i * j;

                if (product == ReverseNumber(product))
                {

#pragma omp critical
                    if (product > greatestProduct)
                        greatestProduct = product;
                }
            }
        }
    }

    return greatestProduct;
}
int ProblemFive()
{
    return std::pow(2,4) * std::pow(3,2) * 5 * 7 * 11 * 13 * 17 * 19;
}
int ProblemSix()
{
    int sumOfSquares = 0;
    int squareOfSum = 0;

#pragma omp parallel
    {
        int localSumOfSquares = 0;
        int localSquareOfSum = 0;

#pragma omp for
        for (int i = 1; i <= 100; i++)
        {
            localSumOfSquares += std::pow(i,2);
            localSquareOfSum += i;
        }

#pragma omp crticial
        {
            sumOfSquares += localSumOfSquares;
            squareOfSum += localSquareOfSum;
        }

    }
    return std::pow(squareOfSum,2) - sumOfSquares;
}
int ProblemSeven()
{
    int n = 10001;
    int upperBound = (int) n * std::log(n) + n * std::log(std::log(n));
    int nthPrime = 0;
    int numPrimes = 0;

    std::vector<int> sieve(upperBound, 1);

#pragma omp parallel
#pragma omp for 
    for (int i = 2; i < upperBound; i++)
        if (sieve[i])
            for (int j = i + i; j < upperBound; j += i)
                sieve[j] = 0;

    for (int i = 2; i < upperBound; i++)
    {
        if (sieve[i])
        {
            numPrimes++;

            if (numPrimes == n)
            {
                nthPrime = i;
                break;
            }
        }
    }

    return nthPrime;
}
