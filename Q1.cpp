#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>

struct Atom {
    double x, y, z;
    double fx, fy, fz;
};

int main() {
    int n = 2000;
    double sigma = 1.0;
    double epsilon = 1.0;
    double total_energy = 0.0;
    std::vector<Atom> atoms(n);

    for (int i = 0; i < n; i++) {
        atoms[i] = { (double)i, (double)(i % 5), (double)(i % 10), 0, 0, 0 };
    }

    double start_time = omp_get_wtime();

    #pragma omp parallel for reduction(+:total_energy) schedule(dynamic, 32)
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double dx = atoms[i].x - atoms[j].x;
            double dy = atoms[i].y - atoms[j].y;
            double dz = atoms[i].z - atoms[j].z;
            double r_sq = dx * dx + dy * dy + dz * dz;

            if (r_sq < 10.0) { 
                double r2_inv = 1.0 / r_sq;
                double r6_inv = r2_inv * r2_inv * r2_inv;
                double term = r6_inv * (2.0 * r6_inv - 1.0);
                double f_val = 24.0 * epsilon * term * r2_inv;

                #pragma omp atomic
                atoms[i].fx += dx * f_val;
                #pragma omp atomic
                atoms[i].fy += dy * f_val;
                #pragma omp atomic
                atoms[i].fz += dz * f_val;
                #pragma omp atomic
                atoms[j].fx -= dx * f_val;
                #pragma omp atomic
                atoms[j].fy -= dy * f_val;
                #pragma omp atomic
                atoms[j].fz -= dz * f_val;

                total_energy += 4.0 * epsilon * r6_inv * (r6_inv - 1.0);
            }
        }
    }

    double end_time = omp_get_wtime();
    std::cout << "Energy: " << total_energy << " Time: " << end_time - start_time << "s" << std::endl;

    return 0;
}