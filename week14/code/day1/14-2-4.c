#include "my.h"
#include <time.h>
#include <sys/time.h>

#define NUM 4

struct argue
{
	int i;
	int b;
	struct timeval timep;
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
	
	pt = (struct argue *)arg;
	sum = 0;
	for(int i = 0; i <= pt->b; ++i)
	{
		sum += i;
	}
	
	r->sum = sum;
	r->tid = pthread_self();
	gettimeofday(&timep, NULL);
	r->st = timep.tv_usec - (pt->timep).tv_usec;
	
	printf("worker thread %d : tid = %p | 0+..+%d sum=%d, time=%ldus\n", pt->i, r->tid, pt->b, r->sum, r->st);
	
	pthread_exit((void *)r);
}

int main()
{
	pthread_t tid[NUM];
	void *r;
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
		pthread_join(tid[i], &r);
		printf(" main: thread %d : tid = %p | 0+..+%d sum=%d, time=%ldus\n", arg[i].i, ((struct res *)r)->tid, arg[i].b, ((struct res *)r)->sum, ((struct res *)r)->st);
		free(r);
		r = NULL;
	}
	
	printf("All finished!\n");
	
	return 0;
}
