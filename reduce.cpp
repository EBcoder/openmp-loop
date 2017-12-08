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
    char staticSch = '1';
    char dynamicSch = '2';
    char guidedSch = '3';
    
    if (argc < 5) {
        std::cerr<<"Usage: "<<argv[0]<<" <n> <nbthreads> <scheduling> <granularity>"<<std::endl;
        return -1;
    }
    omp_set_num_threads(atoi(argv[2]));
    char scheduling1 = *argv[3];
   // std::string dynamSched ("dynamic");
    //std::string statSched ("static");
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
    
    if(scheduling1 == staticSch)
    {
        omp_set_schedule(omp_sched_static, atoi(argv[4]));
    }
    else if(scheduling1 == dynamicSch)
    {
        omp_set_schedule(omp_sched_dynamic, atoi(argv[4]));
    }
    else if(scheduling1 == guidedSch)
    {
        omp_set_schedule(omp_sched_guided, atoi(argv[4]));
    }
    std::chrono::high_resolution_clock::time_point startTime;
    startTime = std::chrono::high_resolution_clock::now();
#pragma omp parallel
    {
#pragma omp single
        {
            for (int i = 0; i < N; i++)
#pragma omp task
            {
                pthread_mutex_lock(&mutex);
                sum = sum + arr[i]
                pthread_unlock_mutex(&mutex);
            }
        }
    }
    std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> elapsed_seconds = endTime-startTime;
    std::cerr<<elapsed_seconds.count()<<std::endl;
    delete[] arr;
    std::cout<<sum<<std::endl;
    return 0;
}
