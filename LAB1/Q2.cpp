#include <iostream>
#include <vector>
#include <omp.h>
#include <iomanip>

const int SIZE = 1000;

void multiply1D(const std::vector<std::vector<double>>& A, 
                const std::vector<std::vector<double>>& B, 
                std::vector<std::vector<double>>& C, int threads) {
    #pragma omp parallel for num_threads(threads)
    for(int i=0; i<SIZE; i++) {
        for(int j=0; j<SIZE; j++) {
            C[i][j] = 0;
            for(int k=0; k<SIZE; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void multiply2D(const std::vector<std::vector<double>>& A, 
                const std::vector<std::vector<double>>& B, 
                std::vector<std::vector<double>>& C, int threads) {
    #pragma omp parallel for collapse(2) num_threads(threads)
    for(int i=0; i<SIZE; i++) {
        for(int j=0; j<SIZE; j++) {
            double sum = 0;
            for(int k=0; k<SIZE; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
}

int main() {
    std::vector<std::vector<double>> matA(SIZE, std::vector<double>(SIZE, 1.1));
    std::vector<std::vector<double>> matB(SIZE, std::vector<double>(SIZE, 2.2));
    std::vector<std::vector<double>> result(SIZE, std::vector<double>(SIZE, 0.0));

    std::cout << std::left << std::setw(10) << "Threads" 
              << std::setw(15) << "1D Time" << "2D Time" << std::endl;

    for(int t : {1, 2, 4, 8, 16}) {
    
        double start1D = omp_get_wtime();
        multiply1D(matA, matB, result, t);
        double end1D = omp_get_wtime();

        double start2D = omp_get_wtime();
        multiply2D(matA, matB, result, t);
        double end2D = omp_get_wtime();

        std::cout << std::left << std::setw(10) << t 
                  << std::fixed << std::setprecision(4) 
                  << std::setw(15) << (end1D-start1D) 
                  << (end2D-start2D) << "s" << std::endl;
    }
    return 0;
}