#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <chrono>
#include <ctime>

#ifdef __cplusplus
extern "C" {
#endif
    
    void generateReduceData (int* arr, size_t n);
    
#ifdef __cplusplus
}
#endif


int main (int argc, char* argv[]) {
    int sum=0;
    int n = 1000000000;
    //forces openmp to create the threads beforehand
#pragma omp parallel
    {
        int fd = open (argv[0], O_RDONLY);
        if (fd != -1) {
            close (fd);
        }
        else {
            std::cerr<<"something is amiss"<<std::endl;
        }
    }
    
    if (argc < 5) {
        std::cerr<<"Usage: "<<argv[0]<<" <n> <nbthreads> <scheduling> <granularity>"<<std::endl;
        return -1;
    }
    int * arr = new int [atoi(argv[1])];
    generateReduceData (arr, atoi(argv[1]));
    //write code here
    std::clock_t c_start = std::clock();
    auto timeStart = std::chrono::high_resolution_clock::now();
    
    std::clock_t c_end = std::clock();
    auto timeEnd = std::chrono::high_resolution_clock::now();
    
    
#pragma omp parallel for reduction(+ : sum)
    for (int i=0; i<n; ++i){
        sum = sum + arr[i];
    }
    // print the time
    std::cout << std::fixed << "Time: "<< 1000.0 * (c_end-c_start) / CLOCKS_PER_SEC << " ms\n" <<
    << std::chrono::duration<double, std::milli>(timeEnd-timeStart).count()
    << " ms\n";
    std::cout<< sum;
    delete[] arr;
    
    return 0;
}
