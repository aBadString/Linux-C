#include "my.h"

void *worker(void *arg)
{
	int TID = pthread_self();
	printf("thread--%d: gettid return %d\n", TID, getpid());
	printf("thread--%d: pthread_self return %p\n", TID, (void *)pthread_self());
	printf("thread--%d: I will exit now.\n", TID);
	pthread_exit(NULL);
	
	return NULL;
}

int main()
{
	pthread_t tid = 0;
	int ret;
	ret = pthread_create(&tid, NULL, worker, NULL);
	//ret = pthread_join(tid, NULL);
	ret = pthread_create(&tid, NULL, worker, NULL);
	ret = pthread_join(tid, NULL);
	ret = pthread_join(tid, NULL);
	
	printf("All finished!\n");
	
	return 0;
}
