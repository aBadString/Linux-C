#include "my.h"
#include <time.h>
#include <sys/time.h>

#define NUM 4

struct argue
{
	int i;
	int b;
	int sum;
	pthread_t tid;
	struct timeval timep;
	long st;
};

void fun(void *arg)
{
	struct argue *pt;
	int sum;
	struct timeval timep;
	
	pt = (struct argue *)arg;
	sum = 0;
	for(int i = 0; i <= pt->b; ++i)
	{
		sum += i;
	}
	
	gettimeofday(&timep, NULL);
	pt->sum = sum;
	pt->tid = pthread_self();
	pt->st = timep.tv_usec - (pt->timep).tv_usec;
}

int main()
{
	pthread_t tid[NUM];
	int ret;
	int i;
	struct argue arg[NUM];
	
	for(i = 0; i < NUM; ++i)
	{
		arg[i].i = i;
		arg[i].b = (i+1)*100;
		gettimeofday(&arg[i].timep, NULL);
		pthread_create(&tid[i], NULL, (void *(*)())fun, (void *)&arg[i]);
	}
	for(i = 0; i < NUM; ++i)
	{
		pthread_join(tid[i], NULL);
		printf("worker thread %d : tid = %p | 0+..+%d sum=%d, time=%ldus\n", arg[i].i, arg[i].tid, arg[i].b, arg[i].sum, arg[i].st);
	}
	
	printf("All finished!\n");
	
	return 0;
}
