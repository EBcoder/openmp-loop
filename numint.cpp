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
    int function_id = atoi(argv[1]);
    int a= atoi(argv[2]);
    int b= atoi(argv[3]);
    int n= atoi(argv[4]);
    int intensity= atoi(argv[5]);

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
    int functionid = atoi(argv[1]);
    int a= atoi(argv[2]);
    int b= atoi(argv[3]);
    int n= atoi(argv[4]);
    int intensity= atoi(argv[5]);
#pragma omp parallel
    for(i=0;i<n;i++){
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
    // print the time
    std::cout << std::fixed << "Time: "<< 1000.0 * (c_end-c_start) / CLOCKS_PER_SEC << " ms\n" <<
    << std::chrono::duration<double, std::milli>(timeEnd-timeStart).count()
    << " ms\n";
    std::cout<< sum;

    

  return 0;
}
