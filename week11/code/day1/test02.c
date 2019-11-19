#include "my.h"

int main()
{
	int pid = fork();
	
	if(pid < 0)
	{
		perror("fork failed!\n");
		return -1;
	}
	else if(pid == 0)
	{
		printf("child %d : running!\n", getpid());
		while(1) continue;
		printf("child %d : exiting!\n", getpid());
		exit(0);
	}
	else
	{
		printf("parent %d : waiting zomble now!\n", getpid());
		sleep(20);
		printf("parent %d : exiting!\n", getpid());
		exit(0);
	}
}
