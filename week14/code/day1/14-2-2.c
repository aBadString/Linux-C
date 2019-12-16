#include "my.h"
#include <time.h>
#include <sys/time.h>

#define NUM 4

struct argue
{
	int i;
	int b;
	struct timeval timep;
	struct res *r;
};

struct res
{
	int sum;
	pthread_t tid;
	long st;
};

void fun(void *arg)
{
	struct argue *pt;
	int sum;
	struct timeval timep;
	struct res *r = malloc(sizeof(struct res));
	
	gettimeofday(&timep, NULL);
	pt = (struct argue *)arg;
	sum = 0;
	for(int i = 0; i <= pt->b; ++i)
	{
		sum += i;
	}
	
	r->sum = sum;
	r->tid = pthread_self();
	r->st = timep.tv_usec - (pt->timep).tv_usec;
	pt->r = r;
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
		printf("worker thread %d : tid = %p | 0+..+%d sum=%d, time=%ldus\n", arg[i].i, arg[i].r->tid, arg[i].b, arg[i].r->sum, arg[i].r->st);
		free(arg[i].r);
		arg[i].r = NULL;
	}
	
	printf("All finished!\n");
	
	return 0;
}
