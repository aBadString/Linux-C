#include "my.h"

static void __attribute__ ((constructor)) before_main(void)
{
	printf("Befored Test1 Main!\n");
}

static void callback1()
{
	printf("callback1 is running!\n");
}
static void callback2()
{
	printf("callback2 is running!\n");
}
static void callback3()
{
	printf("callback3 is running!\n");
}

int main(int argc, char *argv[])
{
	int i;
	atexit(callback1);
	atexit(callback2);
	atexit(callback3);
	
	printf("test01: pid=%d, ppid=%d\n", getpid(), getppid());
	for(int i=0; i < argc; i++)
	{
		printf("test01: %d : %s\n", i, argv[i]);
	}
	
	printf("test01 main finished!\n");
	
	/*
	while(1)
	{
		sleep(1);
	}*/
	
	return 0;
}
