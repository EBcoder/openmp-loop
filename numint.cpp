#include <stdlib.h>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

float f1(float x, int intensity);
float f2(float x, int intensity);
float f3(float x, int intensity);
float f4(float x, int intensity);

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
  
  if (argc < 9) {
    std::cerr<<"Usage: "<<argv[0]<<" <functionid> <a> <b> <n> <intensity> <nbthreads> <scheduling> <granularity>"<<std::endl;
    return -1;
  }
    int sum=0;
    char staticSch = '1';
    char dynamicSch = '2';
    char guidedSch = '3';
    char scheduling1 = *argv[7];
   

    int functionid = atoi(argv[1]);
    int a= atoi(argv[2]);
    int b= atoi(argv[3]);
    int n= atoi(argv[4]);
    int intensity= atoi(argv[5]);
    omp_set_num_threads(atoi(argv[6]));
    
    if(scheduling1 == staticSch)
    {
        omp_set_schedule(omp_sched_static, atoi(argv[8]));
    }
    else if(scheduling1 == dynamicSch)
    {
        omp_set_schedule(omp_sched_dynamic, atoi(argv[8]));
    }
    else if(scheduling1 == guidedSch)
    {
        omp_set_schedule(omp_sched_guided, atoi(argv[8]));
    }
    std::chrono::high_resolution_clock::time_point startTime;
    startTime = std::chrono::high_resolution_clock::now();
    
#pragma omp parallel for reduction(+: sum) schedule(runtime)
    for(int i=0;i<n;i++){
        float x = (a + (i + 0.5) * ((b-a)/n));
        if(atoi(argv[1]) == 1){
            sum = sum + f1(x,intensity)*((b-a)/n);
        }else if(atoi(argv[1]) == 2){
            sum = sum + f1(x,intensity)*((b-a)/n);
        }else if(atoi(argv[1]) == 3){
            sum = sum + f1(x,intensity)*((b-a)/n);
        }else if(atoi(argv[1]) == 4){
            sum = sum + f1(x,intensity)*((b-a)/n);
        }
    }
    std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> elapsed_seconds = endTime-startTime;
    std::cout<< sum;
    std::cerr<<elapsed_seconds.count()<<std::endl;
  return 0;
}
