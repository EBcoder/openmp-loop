#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <algorithm>
#include <chrono>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif
    
    void generateMergeSortData (int* arr, size_t n);
    void checkMergeSortResult (int* arr, size_t n);
    
    
#ifdef __cplusplus
}
#endif

void merge(int* arr, int left, int mid, int rig)
{
    
    int i, j, k;
    int first = mid - left + 1;
    int second =  rig - mid;
    
    
    int *L = new int[first];
    int *R = new int[second];
    
    
    for (i = 0; i < first; i++)
        L[i] = arr[left + i];
    for (j = 0; j < second; j++)
        R[j] = arr[mid + 1+ j];

    i = 0;
    j = 0;
    k = left;
    while (i < first && j < second)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            ++i;
        }
        else
        {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }
    while (i < first)
    {
        arr[k] = L[i];
        ++i;
        ++k;
    }
    while (j < second)
    {
        arr[k] = R[j];
        ++j;
        ++k;
    }

}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l+(r-l)/2;
#pragma omp task
        mergeSort(arr, l, m);
#pragma omp task
        mergeSort(arr, m+1, r);
#pragma taskwait
        merge(arr, l, m, r);
    }
    
    
    
}

int main (int argc, char* argv[]) {
    
    char staticSch = '1';
    char dynamicSch = '2';
    char guidedSch = '3';
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
    
    generateMergeSortData (arr, atoi(argv[1]));
    
    //write code here
    int n = atoi(argv[1]);
    int nbthreads = atoi(argv[1]);
    int* temp = new int[n];
    int i=0;
    int gran = 2;
    std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
    mergeSort(arr, i, i+gran);
    std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> elapsed_seconds = endTime-startTime;
    std::cerr<<elapsed_seconds.count()<<std::endl;
    
    
    checkMergeSortResult (arr, atoi(argv[1]));
    
    delete[] arr;
    
    return 0;
}

