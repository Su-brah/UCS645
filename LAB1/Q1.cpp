#include<iostream>
#include<omp.h>
#include<bits/stdc++.h>
#include<iomanip>

void daxpy(int n, double a ,std::vector<double> &x, std::vector<double> &y,int num_threads){
    #pragma omp parallel for num_threads(num_threads)
    for(int i=0;i<n;i++){
        x[i] = a*x[i] + y[i];
    }
}

int main(){
    const int N= std::pow(2,28);
    const double A=3.5;
    std::vector<double> x(N,1.0);
    std::vector<double> y(N,2.0);
    std::cout << std::left << std::setw(10) << "Threads" << std::setw(15) << "Time (sec)" << "Speedup" << std::endl;
    double base_time =0.0;
    for(int num_threads=1;num_threads<=32;num_threads*=2){
        double start=omp_get_wtime();
        daxpy(N,A,x,y,num_threads);
        double end=omp_get_wtime();
        double time_taken = end - start;
        if(num_threads==1){
            base_time = time_taken;
        }
        double speedup = base_time / time_taken;
        std::cout << std::left << std::setw(10) << num_threads
          << std::fixed << std::setprecision(8) << std::setw(15) << time_taken
          << std::setprecision(2) << speedup << "x" << std::endl;
    }
    return 0;
}