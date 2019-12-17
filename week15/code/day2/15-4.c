#include "my.h"
pthread_cond_t g_cond;
pthread_mutex_t g_mutex=PTHREAD_MUTEX_INITIALIZER;
void worker1(void)
{
	int i;
	pthread_mutext_lock(g_mutex);
	pthread_cond_wait(&g_cond,&g_mutex);
	for(i=0;i<2;i++)
		printf("worker1 is running!\n");
	sleep(1);
	pthread_cond_signal(&g_cond);
	pthread_mutex_unlock(&g_mutex);
}
int main()
{
	pthread_t tid[2];;
	pthread_mutex_init(&g_mutex,NULL);
	pthread_cond_init(&g_cond,NULL);
	int i,ret;
	ret=pthread_creat(&tid[0],NULL,(void*)worker,NULL);
	if(ret!=0)
	{
		perror("thread 1 failed!\n");
		exit(1);
	}
	sleep(5);
	pthread_mutext_lock(g_mutex);
	pthread_cond_signal(&g_cond);
	pthread_mutex_unlock(g_mutex);
	pthread_join(tid[0],NULL);
	pthread_cond_destroy(&g_cond);
	pthread_mutex_destroy(g_mutex);
	return 0;
}
