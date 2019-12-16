#include "my.h"

void * threadfun()
{
	printf("pid = %d : worker thread is running !\n",getpid());
}

int main()
{
	pthread_t tid;
	int error = pthread_create(&tid ,NULL,threadfun,NULL);
	if(error != 0)
	{
		perror("thread create failed! \n");
		return -1;
	}
	printf("master thread pid %d ,work thread tid=%ls \n",getpid(),tid);
	pthread_join(tid ,NULL);
	return 0;
}
