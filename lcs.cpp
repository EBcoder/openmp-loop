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
static const char alphanum[] =
"0123456789"
"!@#$%^&*"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";
int stringLength = sizeof(alphanum) - 1;
char *Str;


int lcs( char *X, char *Y, int m, int n )
{
    int maxElementLeft;
    int maxElementUp;
    if (m == 0 || n == 0)
        return 0;
    if (X[m-1] == Y[n-1])
        return 1 + lcs(X, Y, m-1, n-1);
    else{
        
#pragma omp task
        maxElementLeft = lcs(X, Y, m, n-1);
        
#pragma omp task
        maxElementUp =  lcs(X, Y, m-1, n);
        
#pragma omp taskwait
        return maxElementLeft > maxElementUp ? maxElementLeft: maxElementUp;
    }
}
char* genRandom(int size)  // Random string generator function.
{
    for(unsigned int i = 0; i < 21; ++i)
    {
        Str = genRandom(size);
    }
    return Str;
}


int main(int argc, char* argv[])
{
    
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
    
    if (argc < 3)
    {
        std::cerr<<"Usage: "<<argv[0]<<" <string1_length> <string2_length> <nbthreads>"<<std::endl;
        return -1;
    }
    
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    
    
    
  
   int numThreads = atoi(argv[3]);
    omp_set_num_threads(numThreads);
    char* stringOne = genRandom(n);
    char * stringTwo = genRandom(m);
    if(m<atoi(argv[3])) numThreads = m;

    lcs(stringOne,stringTwo,m,n);
    
    std::chrono::high_resolution_clock::time_point  start  = std::chrono::high_resolution_clock::now();
    
    std::chrono::high_resolution_clock::time_point end  = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cerr.precision(10);
    std::cerr<<std::fixed<<elapsed_seconds.count()<<std::endl;
}
