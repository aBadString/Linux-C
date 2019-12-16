#include "my.h"

#define NUM 4

struct argue
{
	int i;
	int b;
};

void fun(void *arg)
{
	struct argue *pt;
	int sum;
	pt = (struct argue *)arg;
	
	sum = 0;
	for(int i = 0; i <= pt->b; ++i)
	{
		sum += i;
	}
	
	printf("worker thread %d : tid = %p | 0+..+%d sum=%d\n", (int)pt->i, pthread_self(), pt->b, sum);
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
		pthread_create(&tid[i], NULL, (void *(*)())fun, (void *)&arg[i]);
	}
	for(i = 0; i < NUM; ++i)
	{
		pthread_join(tid[i], NULL);
	}
	
	printf("All finished!\n");
	
	return 0;
}
