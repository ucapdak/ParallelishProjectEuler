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
long ProblemEight()
{
    int digits[] = {7,3,1,6,7,1,7,6,5,3,1,3,3,0,6,2,4,9,1,9,2,2,5,1,1,9,6,7,4,4,2,6,5,7,4,
                      7,4,2,3,5,5,3,4,9,1,9,4,9,3,4,9,6,9,8,3,5,2,0,3,1,2,7,7,4,5,0,6,3,2,
                      6,2,3,9,5,7,8,3,1,8,0,1,6,9,8,4,8,0,1,8,6,9,4,7,8,8,5,1,8,4,3,8,5,8,
                      6,1,5,6,0,7,8,9,1,1,2,9,4,9,4,9,5,4,5,9,5,0,1,7,3,7,9,5,8,3,3,1,9,5,
                      2,8,5,3,2,0,8,8,0,5,5,1,1,1,2,5,4,0,6,9,8,7,4,7,1,5,8,5,2,3,8,6,3,0,
                      5,0,7,1,5,6,9,3,2,9,0,9,6,3,2,9,5,2,2,7,4,4,3,0,4,3,5,5,7,6,6,8,9,6,
                      6,4,8,9,5,0,4,4,5,2,4,4,5,2,3,1,6,1,7,3,1,8,5,6,4,0,3,0,9,8,7,1,1,1,
                      2,1,7,2,2,3,8,3,1,1,3,6,2,2,2,9,8,9,3,4,2,3,3,8,0,3,0,8,1,3,5,3,3,6,
                      2,7,6,6,1,4,2,8,2,8,0,6,4,4,4,4,8,6,6,4,5,2,3,8,7,4,9,3,0,3,5,8,9,0,
                      7,2,9,6,2,9,0,4,9,1,5,6,0,4,4,0,7,7,2,3,9,0,7,1,3,8,1,0,5,1,5,8,5,9,
                      3,0,7,9,6,0,8,6,6,7,0,1,7,2,4,2,7,1,2,1,8,8,3,9,9,8,7,9,7,9,0,8,7,9,
                      2,2,7,4,9,2,1,9,0,1,6,9,9,7,2,0,8,8,8,0,9,3,7,7,6,6,5,7,2,7,3,3,3,0,
                      0,1,0,5,3,3,6,7,8,8,1,2,2,0,2,3,5,4,2,1,8,0,9,7,5,1,2,5,4,5,4,0,5,9,
                      4,7,5,2,2,4,3,5,2,5,8,4,9,0,7,7,1,1,6,7,0,5,5,6,0,1,3,6,0,4,8,3,9,5,
                      8,6,4,4,6,7,0,6,3,2,4,4,1,5,7,2,2,1,5,5,3,9,7,5,3,6,9,7,8,1,7,9,7,7,
                      8,4,6,1,7,4,0,6,4,9,5,5,1,4,9,2,9,0,8,6,2,5,6,9,3,2,1,9,7,8,4,6,8,6,
                      2,2,4,8,2,8,3,9,7,2,2,4,1,3,7,5,6,5,7,0,5,6,0,5,7,4,9,0,2,6,1,4,0,7,
                      9,7,2,9,6,8,6,5,2,4,1,4,5,3,5,1,0,0,4,7,4,8,2,1,6,6,3,7,0,4,8,4,4,0,
                      3,1,9,9,8,9,0,0,0,8,8,9,5,2,4,3,4,5,0,6,5,8,5,4,1,2,2,7,5,8,8,6,6,6,
                      8,8,1,1,6,4,2,7,1,7,1,4,7,9,9,2,4,4,4,2,9,2,8,2,3,0,8,6,3,4,6,5,6,7,
                      4,8,1,3,9,1,9,1,2,3,1,6,2,8,2,4,5,8,6,1,7,8,6,6,4,5,8,3,5,9,1,2,4,5,
                      6,6,5,2,9,4,7,6,5,4,5,6,8,2,8,4,8,9,1,2,8,8,3,1,4,2,6,0,7,6,9,0,0,4,
                      2,2,4,2,1,9,0,2,2,6,7,1,0,5,5,6,2,6,3,2,1,1,1,1,1,0,9,3,7,0,5,4,4,2,
                      1,7,5,0,6,9,4,1,6,5,8,9,6,0,4,0,8,0,7,1,9,8,4,0,3,8,5,0,9,6,2,4,5,5,
                      4,4,4,3,6,2,9,8,1,2,3,0,9,8,7,8,7,9,9,2,7,2,4,4,2,8,4,9,0,9,1,8,8,8,
                      4,5,8,0,1,5,6,1,6,6,0,9,7,9,1,9,1,3,3,8,7,5,4,9,9,2,0,0,5,2,4,0,6,3,
                      6,8,9,9,1,2,5,6,0,7,1,7,6,0,6,0,5,8,8,6,1,1,6,4,6,7,1,0,9,4,0,5,0,7,
                      7,5,4,1,0,0,2,2,5,6,9,8,3,1,5,5,2,0,0,0,5,5,9,3,5,7,2,9,7,2,5,7,1,6,
                      3,6,2,6,9,5,6,1,8,8,2,6,7,0,4,2,8,2,5,2,4,8,3,6,0,0,8,2,3,2,5,7,5,3,
                      0,4,2,0,7,5,2,9,6,3,4,5,0};

    long product = 0;
    long largestProduct = 0;
    int numDigits = 13;

#pragma omp parallel
#pragma omp for private(product) 
    for (int i = 0; i <= 1000 - numDigits; i++)
    {
        product = 1;

        for (int j = i; j < i + numDigits; j++)
        {
            product *= digits[j];
        }

#pragma omp critical
        if (product > largestProduct)
            largestProduct = product; 
    }

    return largestProduct;
}
long ProblemNine()
{
    long m;
    long n;
    long a;
    long b;
    long c;

    for (m = 1; m <= 500; m++)
    {
        if (500 % m == 0)
        {
            n = (500/m) - m;

            a = 2 * m * n;
            b = pow(m,2) - pow(n,2);
            c = pow(m,2) + pow(n,2);

            if (b < 0)
                continue;

            if (pow(a,2) + pow(b,2) == pow(c,2))
                break;
        }
    }

    return a * b * c;
}
