#include "my.h"

#define NUM 8

char *message[NUM];
struct data
{
	int id;
	int sum;
	char *message;
};
struct data arr[NUM];

void *printHello(void *arg)
{
	int kid, sum;
	char *msg;
	struct data *mydata;
	sleep(1);
	mydata = (struct data *)arg;
	kid = mydata->id;
	sum = mydata->sum;
	msg = mydata->message;
	printf("Thread %d: %s sum=%d\n", kid, msg, sum);
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	pthread_t threads[NUM];
	int *kids[NUM];
	int rc, t, sum;
	sum = 0;
	message[0] = "123";
	message[1] = "567";
	message[2] = "dfg";
	message[3] = "43v";
	message[4] = "jfs";
	message[5] = "1zuy";
	message[6] = "juybv";
	message[7] = "cccccc";
	
	for(t = 0; t < NUM; ++t)
	{
		sum = sum + t;
		arr[t].id = t;
		arr[t].sum = sum;
		arr[t].message = message[t];
		printf("Create thread %d\n", t);
		rc = pthread_create(&threads[t], NULL, printHello, (void *)&arr[t]);
		if(rc)
		{
			printf("error : return code is %d\n", rc);
			exit(-1);
		}
	}
	
	pthread_exit(NULL);
}
