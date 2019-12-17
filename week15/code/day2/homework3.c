#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
 
 
#define CUSTOM_COUNT 1
#define PRODUCT_COUNT 4
#define BUFFER_SIZE 5 
 
int nNum, nLoop;
int g_count = 0;
int buffer[BUFFER_SIZE];					//缓冲区
int head=0;									//缓冲池读取指针
int wpoint=0; 								//缓冲池写入指针
 
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
 
void *consume(void *arg)
{
	while(1){
		int data;
		
		pthread_mutex_lock(&mutex);
		data = buffer[head];
		head = (head + 1) % BUFFER_SIZE;
        while(((wpoint-head+BUFFER_SIZE)%BUFFER_SIZE) == 0){//醒来以后需要重新判断条件是否满足,如果不满足，再次等待
            printf("consume is waiting: %lu\n", pthread_self());
            pthread_cond_wait(&cond, &mutex);
				}
        printf("consume is %lu, buffer is %d\n", pthread_self(), (wpoint-head+BUFFER_SIZE)%BUFFER_SIZE);
        g_count--;
	    pthread_mutex_unlock(&mutex);	
        sleep(1);
	}
	pthread_exit(NULL);
}
 
void *produce(void *arg)
{
    while(1){
        pthread_mutex_lock(&mutex);
		buffer[wpoint] = 1;
		wpoint = (wpoint + 1) % BUFFER_SIZE;
        if(((wpoint-head+BUFFER_SIZE)%BUFFER_SIZE) >= BUFFER_SIZE){
            printf("产品太多，休眠1秒\n");
            pthread_mutex_unlock(&mutex);
            sleep(1);
            continue;
        }
   //不用解锁再上锁，因为如果大于BUFFER_SIZE，会解锁，但是会continue,不会执行下面的语句，会重新从头开始，上锁； 
        printf("start produce the product\n");
        g_count++;
        printf("produce is %lu, buffer is %d\n", pthread_self(), (wpoint-head+BUFFER_SIZE)%BUFFER_SIZE);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
	pthread_exit(NULL);
}
 
int main()
{
	int i = 0;
	pthread_t tidCustom[CUSTOM_COUNT];
	pthread_t tidProduce[PRODUCT_COUNT];
	
	/*创建消费者线程*/
	for (i = 0; i < CUSTOM_COUNT; ++i){
		pthread_create(&tidCustom[i], NULL, consume, NULL);
	}
 
	sleep(3);
 
	/*创建生产者线程*/
	for (i = 0; i < PRODUCT_COUNT; ++i){
		pthread_create(&tidProduce[i], NULL, produce, NULL);
	}
 
	/*等待消费者线程*/
	for (i = 0; i < CUSTOM_COUNT; ++i){
		pthread_join(tidCustom[i], NULL);
	}
	
	/*等待生产者线程*/
	for (i = 0; i < PRODUCT_COUNT; ++i){
		pthread_join(tidProduce[i], NULL);
	}
	
	printf("parent exit\n");
	exit(0);
}
