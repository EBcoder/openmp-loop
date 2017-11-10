#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <algorithm>

#ifdef __cplusplus
extern "C" {
#endif
  void generateMergeSortData (int* arr, size_t n);
  void checkMergeSortResult (int* arr, size_t n);
#ifdef __cplusplus
}
#endif
void merge(int * arr, int value, int * temporaryNumberArr)
{
    int b= 0;
    int a  = value / 2;
    int temporaryNumber = 0;
    while (b< value / 2 && a  < value)
    {
        if (arr[b] < arr[a ]){
            temporaryNumberArr[temporaryNumber = arr[b];
            b++;
            temporaryNumber++;
        }
        else{
            temporaryNumberArr[temporaryNumber = arr[a ];
            a++;
            temporaryNumber++;
        }
    }
    while (b< value / 2)
    {
        temporaryNumberArr[temporaryNumber = arr[b];
        temporaryNumber++; b++;
    }
    while (a  < value){
        temporaryNumberArr[temporaryNumber = arr[a];
        temporaryNumber++; a++;
    }
    memcpy(arr, temporaryNumberArr, value * sizeof(int));
}

//
void mergesort(int * X, int n, int * tmp)
{
    if (n < 2) return;
    
#pragma omp task firstprivate (X, n, tmp)
    mergesort(X, n/2, tmp);
    
#pragma omp task firstprivate (X, n, tmp)
    mergesort(X+(n/2), n-(n/2), tmp);
    
#pragma omp taskwait
    
    /* merge sorted balves into sorted list */
    merge(X, n, tmp);
}
void merge(int * X, int n, int * tmp) {
    int i = 0;
    int j = n/2;
    int ti = 0;
    
    while (i<n/2 && j<n) {
        if (X[i] < X[j]) {
            tmp[ti] = X[i];
            ti++; i++;
        } else {
            tmp[ti] = X[j];
            ti++; j++;
        }
    }
    while (i<n/2) { /* finish up lower half */
        tmp[ti] = X[i];
        ti++; i++;
    }
    while (j<n) { /* finish up upper half */
        tmp[ti] = X[j];
        ti++; j++;
    }
    memcpy(X, tmp, n*sizeof(int));
    
}

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
  int* temporaryNumberArr = new int[atoi(argv[1])];
  int nbthreads = atoi(argv[1]);
  generateMergeSortData (arr, atoi(argv[1]));
  
  //write code here
    for(int i=0; i<atoi(argv[1]); i++){
        arr[i] = (rand()%100)+1;
    }
    
#pragma omp parallel {
    
}
std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();


mSort(arr, atoi(argv[1]), temporaryNumberArr);


std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
std::chrono::duration<double> elapsed_seconds = end-start;
std::cerr<<elapsed_seconds.count()<<std::endl;


checkMergeSortResult (arr, n);



  checkMergeSortResult (arr, atoi(argv[1]));
  
  delete[] arr;

  return 0;
}
