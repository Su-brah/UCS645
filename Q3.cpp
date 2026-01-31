#include <iostream>
#include <omp.h>
#include <iomanip>

int main() {
    long num_steps = 100000000;
    double step = 1.0/(double)num_steps;

    std::cout << std::left << std::setw(10) << "Threads" << std::setw(15) << "Time" << "Pi Value" << std::endl;

    for(int t : {1, 2, 4, 8, 16}) {
        double sum = 0.0;
        double start = omp_get_wtime();

        #pragma omp parallel for num_threads(t) reduction(+:sum)
        for(int i=0; i<num_steps; i++) {
            double x = (i+0.5)*step;
            sum = sum + 4.0/(1.0+x*x);
        }

        double pi = step * sum;
        double end = omp_get_wtime();

        std::cout << std::left << std::setw(10) << t 
                  << std::fixed << std::setprecision(6) << std::setw(15) << (end-start) 
                  << std::setprecision(10) << pi << std::endl;
    }

    return 0;
}