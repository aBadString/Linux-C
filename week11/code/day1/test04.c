#include "my.h"

int main()
{
	int pid1, pid2, s1, s2, p1, p2;
	
	if( ((pid1 = fork()) && (pid2 = fork())) < 0 )
	{
		perror("fork failed!\n");
		return -1;
	}
	else if(pid1 == 0)
	{
		printf("%d : child1 is running now!\n", getpid());
		printf("%d : child1 is exit now!\n", getpid());
		//while(1) continue;
		exit(120);
	}
	else if(pid2 == 0)
	{
		printf("%d : child2 is running now!\n", getpid());
		printf("%d : child2 is exit now!\n", getpid());
		//while(1) continue;
		exit(130);
	}
	else
	{
		//sleep(5);
		printf("%d : parent waiting zomble now!\n", getpid());
		p1 = wait(&s1);
		p2 = wait(&s2);
		printf("%d  %d\n", WEXITSTATUS(s1), WEXITSTATUS(s2));
		if(WEXITSTATUS(s1) == 120)
		{
			printf("child1 %d\n", p1);
		}
		exit(0);
	}
}
