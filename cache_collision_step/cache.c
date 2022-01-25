#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
int main()
{
    int*a = malloc(8*1024*1024*sizeof(int));
    memset(a, 1, 8*1024*1024*sizeof(int));
    struct timespec start, finish;
    double elapsed;
    clock_gettime(CLOCK_MONOTONIC, &start); 
    int p = 0;
    for(int i = 0; i < 1024*1024; i++)
    {
	a[p]--;
	p+=255;
	if(p > 1024*1024*8) p = 0;
    }
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("p is 255 using time:%f \r\n",elapsed);

    clock_gettime(CLOCK_MONOTONIC, &start);
    p = 0;
    for(int i = 0; i < 1024*1024; i++)
    {
        a[p]--;
        p+=256;
        if(p > 1024*1024*8) p = 0;
    }
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("p is 256 using time:%f \r\n",elapsed);

    clock_gettime(CLOCK_MONOTONIC, &start);
    p = 0;
    for(int i = 0; i < 1024*1024; i++)
    {
        a[p]--;
        p+=257;
        if(p > 1024*1024*8) p = 0;
    }
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("p is 257 using time:%f \r\n",elapsed);
}
