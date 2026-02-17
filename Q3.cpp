#include <iostream>
#include <vector>
#include <omp.h>

int main() {
    const int size = 400;
    const int steps = 500;
    std::vector<std::vector<double>> grid(size, std::vector<double>(size, 25.0));
    std::vector<std::vector<double>> next_grid(size, std::vector<double>(size, 25.0));

    for (int i = 0; i < size; i++) grid[i][0] = 100.0; 

    double start_time = omp_get_wtime();

    for (int t = 0; t < steps; t++) {
        double total_heat = 0.0;

        #pragma omp parallel for reduction(+:total_heat) collapse(2) schedule(static)
        for (int i = 1; i < size - 1; i++) {
            for (int j = 1; j < size - 1; j++) {
                next_grid[i][j] = 0.25 * (grid[i + 1][j] + grid[i - 1][j] + 
                                          grid[i][j + 1] + grid[i][j - 1]);
                total_heat += next_grid[i][j];
            }
        }

        #pragma omp parallel for collapse(2)
        for (int i = 1; i < size - 1; i++) {
            for (int j = 1; j < size - 1; j++) {
                grid[i][j] = next_grid[i][j];
            }
        }
        
        if (t % 100 == 0) std::cout << "Step " << t << " Total Heat: " << total_heat << std::endl;
    }

    double end_time = omp_get_wtime();
    std::cout << "Simulation finished in: " << end_time - start_time << "s" << std::endl;

    return 0;
}