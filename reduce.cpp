#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


#ifdef __cplusplus
extern "C" {
#endif

  void generateReduceData (int* arr, size_t n);
  
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
  
  if (argc < 5) {
    std::cerr<<"Usage: "<<argv[0]<<" <n> <nbthreads> <scheduling> <granularity>"<<std::endl;
    return -1;
  }

  int * arr = new int [atoi(argv[1])];
  generateReduceData (arr, atoi(argv[1]));
    int sum =0;
    double timeStart,time;
    int tId = omp_get_thread_num();
    int numThread = omp_get_num_threads();
    
    timeStart = omp_get_wtime();
    

  // write code here
    for(int i=0; i<atoi(argv[1]); i++){
        arr[i] = (rand()%100)+1;
        sum = sum + arr[i];
    }
#pragma omp parallel for reduction(+:sum)
    for(int i=0; i<atoi(argv[1]); i++){
        sum = sum + arr[i];
    }
    
    time = omp_get_wtime() - timeStart;
    std::cout << sum <<std::endl;
    std::cerr<<time<<std::endl;
  delete[] arr;

  return 0;
}
