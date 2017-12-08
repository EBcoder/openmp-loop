#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <ctime>
#include <ratio>
#include <chrono>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif
    
    void generateReduceData (int* arr, size_t n);
    
#ifdef __cplusplus
}
#endif


int main (int argc, char* argv[]) {
    int sum=0;
    int n ;
    
    
    if (argc < 5) {
        std::cerr<<"Usage: "<<argv[0]<<" <n> <nbthreads> <scheduling> <granularity>"<<std::endl;
        return -1;
    }
    
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

    int * arr = new int [atoi(argv[1])];
    generateReduceData (arr, atoi(argv[1]));
    
    int n = atoi(argv[1]);
    //write code here
    omp_set_num_threads(atoi(argv[2]));
    std::string dynamSched ("dynamic");
    std::string statSched ("static");
    if(statSched.compare(atoi(argv[3])==0)
    {
        omp_set_schdule(omp_sched_static,atoi(argv[4]));
    }else if (dynamSched.compare(atoi(argv[3])==0))
    {
            omp_set_schdule(omp_sched_dynamic,atoi(argv[4]));
    }else
       {
           omp_set_schedule(omp_sched_guided,atoi(argv[4]));
       }
    std::chrono::high_resolution_clock::time_point startTime;
    start = std::chrono::high_resolution_clock::now();
#pragma omp parallel for reduction(+ : sum)
    for (int i=0; i<n; ++i){
        sum = sum + arr[i];
    }
    std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> elapsed_seconds = endTime-startTime;
    std::cerr<<elapsed_seconds.count()<<std::endl;
    delete[] arr;
    std::cout<<sum<<std::endl;
    return 0;
}
