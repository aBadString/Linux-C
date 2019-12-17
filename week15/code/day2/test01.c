#include <pthread.h>
#include <stdio.h>
#define NUM_THREADS 3
#define TCOUNT 10
#define COUNT_LIMIT 12

int count = 0;
int thread_ids[3]={0,1,2};
pthread_mutex_t count_mutex;
pthread_cond_t count_threshold_cy;

void *watch_count(void *idp){
	int *my_id=idp;
	printf("Starting watch_count():thread %d\n",my_id);
	pthread_mutex_lock(&count_mutex);
	if(count<COUNT_LIMIT){
		pthread_cond_wait(&count_threshold_cy,&count_mutex);
		printf("watch_count():thread %d Condition signal received.\n",*my_id);
	}
	pthread_mutex_unlock(&count_mutex);
	pthread_exit(NULL);
}

void *inc_count(void *idp){
	int i,j;
	double result=0.0;
	int *my_id=idp;
	for(i=0;i<TCOUNT;i++){
		pthread_mutex_lock(&count_mutex);
		count++;
		if(count==COUNT_LIMIT){
			pthread_cond_signal(&count_threshold_cy);
			printf("inc_count():thread %d , count = %d Threshold reached.\n",*my_id,count);
		}
		printf("inc_count():thread %d,count = %d, unlocking mutex\n",*my_id,count);
		pthread_mutex_unlock(&count_mutex);
		for(j=0;j<1000;j++){
			result = result+(double)random();
		}
	}
	pthread_exit(NULL);
}

int main(int argc, char *argv[]){
	int i,rc;
	pthread_t threads[3];
	pthread_attr_t attr;
	pthread_mutex_init(&count_mutex,NULL);
	pthread_cond_init(&count_threshold_cy,NULL);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	pthread_create(&threads[0],&attr,inc_count,(void *)&thread_ids[0]);
	pthread_create(&threads[1],&attr,inc_count,(void *)&thread_ids[1]);
	pthread_create(&threads[2],&attr,watch_count,(void *)&thread_ids[2]);
	for(i=0;i<NUM_THREADS;i++){
		pthread_join(threads[i],NULL);
	}
	printf("Main():Waited on %d threads.Done.\n",NUM_THREADS);
	pthread_attr_destroy(&attr);
	pthread_mutex_destroy(&count_mutex);
	pthread_cond_destroy(&count_threshold_cy);
	pthread_exit(NULL);
}
