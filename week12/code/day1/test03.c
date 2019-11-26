#include "my.h"

int main()
{
	pid_t p1, p2, p3;
	
	p1 = fork();	
	if(p1 < 0)
	{
		perror("fork1 failed.\n");
		return -1;
	}
	else if(p1 == 0)
	{
		printf("child1: pid=%d ppid=%d\n", getpid(), getppid());
		exit(0);
	}
	else
	{
		p2 = fork();
		if(p2 < 0)
		{
			perror("fork2 failed.\n");
			return -1;
		}
		else if(p2 == 0)
		{
			printf("child2: pid=%d ppid=%d\n", getpid(), getppid());
			exit(0);
		}
		else
		{
			p3 = fork();
			if(p3 < 0)
			{
				perror("fork3 failed.\n");
				return -1;
			}
			else if(p3 == 0)
			{
				printf("child3: pid=%d ppid=%d\n", getpid(), getppid());
				exit(0);
			}
			else
			{
				wait(NULL);
			}
			wait(NULL);
		}
		wait(NULL);
		printf("parent: end\n");
		exit(0);
	}
}
