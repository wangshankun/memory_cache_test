#include <iostream>
#include <algorithm> 
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <sched.h>
#include <ctype.h>
#include <string.h>
#include <pthread.h>
#include <stdint.h>

#include "thread_pool.h"

using namespace std;

#define CYC_NUM 100000000
#define MAX_THREAD_NUM 4

struct data_per_cpu_128
{
	uint32_t data;//4bytes
	uint8_t  padding[124];
}test_128[MAX_THREAD_NUM];

struct data_per_cpu_64
{
	uint32_t data;
	uint8_t  padding[60];
}test_64[MAX_THREAD_NUM];

# pragma pack (1)//防止默认对齐到64bytes
struct data_per_cpu_63
{
	uint32_t data;
	uint8_t  padding[59];
}test_63[MAX_THREAD_NUM];

struct data_per_cpu_32
{
	uint32_t data;
	uint8_t  padding[28];
}test_32[MAX_THREAD_NUM];


uint32_t func_32(data_per_cpu_32* arg, int id)
{
    //绑定CPU
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(id, &mask);
    if( sched_setaffinity(0, sizeof(mask), &mask) == -1)
    {
        fprintf(stderr, "WARNING: Could not set CPU Affinity \r\n"); 
    }
    else
    {
        //fprintf(stderr, "Bind process #%d to CPU #%d \r\n", id, id); 
    }
    
    //do some cpu expensive operation
    int cnt = CYC_NUM;
	
    while(cnt--)
    {
        arg[id].data++;
    }

    return arg[id].data;
}

uint32_t func_63(data_per_cpu_63* arg, int id)
{
    //绑定CPU
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(id, &mask);
    if( sched_setaffinity(0, sizeof(mask), &mask) == -1)
    {
        fprintf(stderr, "WARNING: Could not set CPU Affinity \r\n"); 
    }
    else
    {
        //fprintf(stderr, "Bind process #%d to CPU #%d \r\n", id, id); 
    }
    
    //do some cpu expensive operation
    int cnt = CYC_NUM;
	
    while(cnt--)
    {
        arg[id].data++;
    }

    return arg[id].data;
}

uint32_t func_64(data_per_cpu_64* arg, int id)
{
    //绑定CPU
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(id, &mask);
    if( sched_setaffinity(0, sizeof(mask), &mask) == -1)
    {
        fprintf(stderr, "WARNING: Could not set CPU Affinity \r\n"); 
    }
    else
    {
        //fprintf(stderr, "Bind process #%d to CPU #%d \r\n", id, id); 
    }
    
    //do some cpu expensive operation
    int cnt = CYC_NUM;
	
    while(cnt--)
    {
        arg[id].data++;
    }

    return arg[id].data;
}

uint32_t func_128(data_per_cpu_128* arg, int id)
{
    //绑定CPU
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(id, &mask);
    if( sched_setaffinity(0, sizeof(mask), &mask) == -1)
    {
        fprintf(stderr, "WARNING: Could not set CPU Affinity \r\n"); 
    }
    else
    {
        //fprintf(stderr, "Bind process #%d to CPU #%d \r\n", id, id); 
    }
    
    //do some cpu expensive operation
    int cnt = CYC_NUM;
	
    while(cnt--)
    {
        arg[id].data++;
    }

    return arg[id].data;
}


int main()
{
	ThreadPool* m_exec_pool  = new ThreadPool(MAX_THREAD_NUM);
	
	memset(test_32,  0, sizeof(test_32));
	memset(test_63,  0, sizeof(test_63));
	memset(test_64,  0, sizeof(test_64));
	memset(test_128, 0, sizeof(test_128));

	double elapsed;
	struct timespec start, finish;
	
	{
		clock_gettime(CLOCK_MONOTONIC, &start);
		long result = 0;
		vector<future<uint32_t>> res_vec;
		for(int i = 0; i < MAX_THREAD_NUM; i++)
		{
			auto res = m_exec_pool->enqueue(func_32, test_32, i);
			res_vec.push_back(move(res));
		}

		for(auto &res: res_vec)
		{
			result = result + res.get();
		}

		clock_gettime(CLOCK_MONOTONIC, &finish);
		elapsed = (finish.tv_sec - start.tv_sec);
		elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
		fprintf(stderr, "result: %ld \r\n",result); 
		printf("test_32 avg elapsed time:%f\r\n",elapsed/MAX_THREAD_NUM);
	}

	{
		clock_gettime(CLOCK_MONOTONIC, &start);
		long result = 0;
		vector<future<uint32_t>> res_vec;
		for(int i = 0; i < MAX_THREAD_NUM; i++)
		{
			auto res = m_exec_pool->enqueue(func_63, test_63, i);
			res_vec.push_back(move(res));
		}

		for(auto &res: res_vec)
		{
			result = result + res.get();
		}

		clock_gettime(CLOCK_MONOTONIC, &finish);
		elapsed = (finish.tv_sec - start.tv_sec);
		elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
		fprintf(stderr, "result: %ld \r\n",result); 
		printf("test_63 avg elapsed time:%f\r\n",elapsed/MAX_THREAD_NUM);
	}

	{
		clock_gettime(CLOCK_MONOTONIC, &start);
		long result = 0;
		vector<future<uint32_t>> res_vec;
		for(int i = 0; i < MAX_THREAD_NUM; i++)
		{
			auto res = m_exec_pool->enqueue(func_64, test_64, i);
			res_vec.push_back(move(res));
		}

		for(auto &res: res_vec)
		{
			result = result + res.get();
		}

		clock_gettime(CLOCK_MONOTONIC, &finish);
		elapsed = (finish.tv_sec - start.tv_sec);
		elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
		fprintf(stderr, "result: %ld \r\n",result); 
		printf("test_64 avg elapsed time:%f\r\n",elapsed/MAX_THREAD_NUM);
	}
	
	{
		clock_gettime(CLOCK_MONOTONIC, &start);
		long result = 0;
		vector<future<uint32_t>> res_vec;
		for(int i = 0; i < MAX_THREAD_NUM; i++)
		{
			auto res = m_exec_pool->enqueue(func_128, test_128, i);
			res_vec.push_back(move(res));
		}

		for(auto &res: res_vec)
		{
			result = result + res.get();
		}

		clock_gettime(CLOCK_MONOTONIC, &finish);
		elapsed = (finish.tv_sec - start.tv_sec);
		elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
		fprintf(stderr, "result: %ld \r\n",result); 
		printf("test_128 avg elapsed time:%f\r\n",elapsed/MAX_THREAD_NUM);
	}
 }
	
 
