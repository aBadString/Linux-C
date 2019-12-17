#include "my.h"
#define SIZE 100
int a[SIZE],b[SIZE];
int max;
pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;

void max_fun(int *arg){
	int *ap=arg;
	int rv,i,l_max;
	for(i=1;i<SIZE;i++){
		if(ap[i]>l_max)
			l_max=ap[i];
	}
	rv=pthread_mutex_lock(&mtx);
	check_error(rv,"mutex_lock");
	if(l_max>max)
		max=l_max;
	rv=pthread_mutex_unlock(&mtx);
	check_error(rv,"mutex_unlock");
	pthread_exit(NULL);
}
int main(void){
	pthread_t tid1,tid2;
	int i,rv;
	for(i=1;i<SIZE;i++){
		a[i]=rand();
		b[i]=rand();
	}
	rv=pthread_create(&tid1,NULL,(void*(*)())max_fun,a);
	check_error(rv,"pthread_create:tid1");
	rv=pthread_create(&tid2,NULL,(void*(*)())max_fun,b);
	check_error(rv,"pthread_create:tid2");

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	printf("max value = %d\n",max);
	exit(0);
}
