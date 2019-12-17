#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
 
#define PRODUCER_NUM 1 //生产者数目
#define CONSUMER_NUM 4 //消费者数目
#define SIZE	 5  //缓冲池大小
int buffer[SIZE];	//缓冲区
int pread=0;	//缓冲池读取指针
int pwrite=0; //缓冲池写入指针
//sem_t room_sem;		//同步信号信号量，表示缓冲区有可用空间
//sem_t product_sem;		//同步信号量，表示缓冲区有可用产品
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void producer_fun(void *arg)
{
	for(int i = 0; /*i < 5*/; i = (i+1)%10)
	{
		sleep(1);
		pthread_mutex_lock(&mutex);
		
		if(((pwrite-pread+SIZE)%SIZE) == SIZE-1)
		{
            printf("producer %d sleep\n", (int)arg);
        }
		else
		{
			//生产者往缓冲池中写入数据
			buffer[pwrite] = i;
			pwrite = (pwrite + 1) % SIZE;
			printf("producer %d write %d to buffer\n", (int)arg, i);
			printf("buffer size is %d\n",(SIZE - (pwrite-pread) - 1)%SIZE);
			
			pthread_cond_signal(&cond);
		}
        pthread_mutex_unlock(&mutex);
	}
}
 
 
void consumer_fun(void *arg)
{
	while(1)
	{
		int data;
		sleep(1);
		
		pthread_mutex_lock(&mutex);
		while(((pwrite-pread+SIZE)%SIZE) == 0)
		{
            printf("consumer %d sleep\n", (int)arg);
            pthread_cond_wait(&cond, &mutex);
		}
		
		//消费者从缓冲池读取数据
		data = buffer[pread];
		pread = (pread + 1) % SIZE;
		printf("consumer %d read %d from buffer\n", (int)arg, data);
		printf("buffer size is %d\n",(SIZE - (pwrite-pread) - 1)%SIZE);
		
		pthread_mutex_unlock(&mutex);
	}
}
 
int main()
{
	int ret;
	pthread_t producer_id[PRODUCER_NUM];
	pthread_t consumer_id[CONSUMER_NUM];
	pthread_mutex_init(&mutex, NULL);	//初始化互斥量
	
	for (int i = 0; i < PRODUCER_NUM; i++)
	{
		//创建生产者线程
		ret =pthread_create(&producer_id[i], NULL, producer_fun, (void*)i);
		if (ret != 0)
		{
			printf("producer_id error");
			exit(0);
		}
	}
	
	for (int i = 0; i < CONSUMER_NUM; i++)
	{
		//创建消费者线程
		ret = pthread_create(&consumer_id[i], NULL, consumer_fun, (void*)i);
		if (ret != 0)
		{
			printf("consumer_id error");
			exit(0);
		}
	}
	
	for(int i=0;i<PRODUCER_NUM;i++)
	{
		pthread_join(producer_id[i],NULL);
	}
	for(int i=0;i<CONSUMER_NUM;i++)
	{
		pthread_join(consumer_id[i],NULL);
	}
 
	exit(0);
}
