#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <omp.h>

int main() {
    std::string seq_a = "GATTACA" + std::string(1000, 'A');
    std::string seq_b = "GCATGCU" + std::string(1000, 'G');
    int n = seq_a.length();
    int m = seq_b.length();

    std::vector<std::vector<int>> matrix(n + 1, std::vector<int>(m + 1, 0));
    int global_max = 0;

    double start_time = omp_get_wtime();

    for (int diag = 1; diag <= n + m; diag++) {
        int row_start = std::max(1, diag - m);
        int row_end = std::min(diag, n);

        #pragma omp parallel for reduction(max:global_max)
        for (int i = row_start; i <= row_end; i++) {
            int j = diag - i + 1;
            if (j <= m) {
                int score = (seq_a[i - 1] == seq_b[j - 1]) ? 2 : -1;
                int val = std::max({0, 
                                   matrix[i - 1][j - 1] + score, 
                                   matrix[i - 1][j] - 1, 
                                   matrix[i][j - 1] - 1});
                matrix[i][j] = val;
                if (val > global_max) global_max = val;
            }
        }
    }

    double end_time = omp_get_wtime();
    std::cout << "Max Score: " << global_max << " Time: " << end_time - start_time << "s" << std::endl;

    return 0;
}