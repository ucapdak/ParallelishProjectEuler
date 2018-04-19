#include "fib.h"

int main(int argc, char ** argv)
{
    omp_set_dynamic(1);
    
    const int num = 35;
    int a;

    double duration;
    std::clock_t start;

    for (int i = 1; i <= 4; i++)
    {
        omp_set_num_threads(i);

#pragma omp parallel shared(a)
#pragma omp single nowait
        {
            std::cout << "Running Fibonacci with " << omp_get_num_threads() << " threads." << std::endl;
            start = std::clock();
            a = fib(num);
            duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
            std::cout << "Fib completed in " << duration << " seconds." << std::endl;
        }
    }
    return 1;
}
