#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctime>
#include <chrono>


#include <ratio>


#ifdef __cplusplus
extern "C" {
#endif
    void generatePrefixSumData (int* arr, size_t n);
    void checkPrefixSumResult (int* arr, size_t n);
    
#ifdef __cplusplus
}
#endif
int main (int argc, char* argv[]) {
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
    if (argc < 3) {
        std::cerr<<"Usage: "<<argv[0]<<" <n> <nbthreads>"<<std::endl;
        return -1;
    }
    int n = atoi(argv[1]);
    int * arr = new int [n];
    int * pr = new int [n+1];
    int *carry;
    int nbthreads = atoi(argv[1]);
    
    
    
    generatePrefixSumData (arr, atoi(argv[1]));
    
    std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();
    //write code here
#pragma omp parallel
{
        int sum = 0;
        int id = omp_get_thread_num();
    #pragma omp single
    {
        nbthreads = omp_get_num_threads();
        carry = new int[nbthreads];
     }
    #pragma for schedule(static)
    for(int i =0; i<atoi(argv[1]);i++)
    {
        sum +=arr[i];
        pr[i+1] =sum;
    }
    carry[id] = sum;
    #pragma barrier
    int offset = 0;
    for(int i=0;i<atoi(argv[1]);i++)
    {
        pr[i+1] +=offset;
    }
 }
    std::chrono::high_resolution_clock::time_point endTime  = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> elapsed_seconds = endTime - startTime;
    
     checkPrefixSumResult(pr, atoi(argv[1]));
    
    std::cerr<<std::fixed<<elapsed_seconds.count()<<std::endl;
    
    
    
    
    delete[] carry;
    delete[] pr;
    delete[] arr;
    return 0;
}

