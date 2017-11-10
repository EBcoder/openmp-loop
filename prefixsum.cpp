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

  int * arr = new int [atoi(argv[1])];

  generatePrefixSumData (arr, atoi(argv[1]));
   float time, timeStart = omp_get_wtime();
  //write code here
  checkPrefixSumResult(pr, atoi(argv[1]));
#pragma omp parallel for 
    for(int i; i = (sizeof(arr)/sizeof(*arr)); i++){
        pr[i] = pr[i-1] + arr [i -1];
        
    }
    void prefixsum (int * arr , int n, int * pr) {
        pr [0] = 0;
    #pragma omp parallel {
    #pragma omp for schedule(static)
            for (int i=1; i <=n; ++i){
                pr[i] = pr[i -1] + arr [i -1];
            }
    #pragma omp for schedule(static)
            for (int i=1; i <=n; ++i){
                sum += pr[i];
            }
        }
    }

    time = omp_get_wtime() - timeStart;
    std::cerr<<time<<std::endl;
  
  delete[] arr;

  return 0;
}
