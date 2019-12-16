#include "my.h"
#include <time.h>
#include <sys/time.h>

#define NUM 4

pthread_t tid[NUM];
long st[NUM];
int sum[NUM];

struct argue
{
	int i;
	int b;
	struct timeval timep;
};

void fun(void *arg)
{
	struct argue *pt;
	struct timeval timep;
	int s;
	
	gettimeofday(&timep, NULL);
	pt = (struct argue *)arg;
	s = 0;
	for(int i = 0; i <= pt->b; ++i)
	{
		s += i;
	}
	
	sum[pt->i] = s;
	tid[pt->i] = pthread_self();
	st[pt->i] = timep.tv_usec - (pt->timep).tv_usec;
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
		printf("worker thread %d : tid = %p | 0+..+%d sum=%d, time=%ldus\n", arg[i].i, tid[i], arg[i].b, sum[i], st[i]);
	}
	
	printf("All finished!\n");
	
	return 0;
}
