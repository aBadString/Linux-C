#include "my.h"

#define SIZE 10

int a[SIZE], b[SIZE];

void max_fun(int *arg)
{
	int *ap = arg;
	int rv, i, k;
	k = 0;
	for(int i = 1; i < SIZE; i++)
	{
		if(ap[i] > ap[k])
			k = i;
	}
	pthread_exit((void *)&ap[k]);
}

int main()
{
	pthread_t tid1, tid2;
	int i, rv, **ptr1, **ptr2;
	
	srand(time(NULL));
	for(i=1; i < SIZE; i++)
	{
		a[i] = rand() % 20;
		b[i] = rand() % 20;
	}
	
	rv = pthread_create(&tid1, NULL, (void *(*)())max_fun, a);
	check_error(rv, "pthread_create tid1");
	rv = pthread_create(&tid2, NULL, (void *(*)())max_fun, b);
	check_error(rv, "pthread_create tid2");
	
	pthread_join(tid1, (void **)&ptr1);
	pthread_join(tid2, (void **)&ptr2);
	printf("thread1: max=%d\n", *ptr1);
	printf("thread2: max=%d\n", *ptr2);
}
