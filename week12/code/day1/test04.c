#include "my.h"

#define NUM 65536

int main()
{
	pid_t p1, p2, p3;
	int fd1[2], fd2[2];
	
	pipe(fd1);
	pipe(fd2);
	
	p1 = fork();	
	if(p1 < 0)
	{
		perror("fork1 failed.\n");
		return -1;
	}
	else if(p1 == 0)
	{
		char buf1[10];
		int wn1;
		
		close(fd1[0]);close(fd2[0]);close(fd2[1]);
		printf("child1: pid=%d ppid=%d\n", getpid(), getppid());
		memset(buf1, 0, 10);
		for(int i = 0; i < NUM; ++i)
		{
			sprintf(buf1, "%d,", i);
			wn1 = write(fd1[1], buf1, 10);
			printf("child1: write(%d) %d\n", wn1, i);
			memset(buf1, 0, 10);
		}
		printf("child1: write over\n");
		close(fd1[1]);
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
			char buf2[10];
			int rn2;
			
			close(fd1[1]);close(fd2[0]);
			printf("child2: pid=%d ppid=%d\n", getpid(), getppid());
			memset(buf2, 0, 10);
			for(int i = 0; (i < NUM) && ((rn2 = read(fd1[0], buf2, 10)) > 0); ++i)
			{
				write(fd2[1], buf2, 10);
				printf("child2: read(%d) write %s\n", rn2, buf2);
				memset(buf2, 0, 10);
			}
			printf("child2: read write over\n");
			close(fd1[0]);(fd2[1]);
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
				int i = 0;
				int sum = 0;
				int rn3;
				char buf3[10];
				
				close(fd1[0]);close(fd1[1]);close(fd2[1]);
				printf("child3: pid=%d ppid=%d\n", getpid(), getppid());
				memset(buf3, 0, 10);
				for(int i = 0; (i < NUM) && ((rn3 = read(fd2[0], buf3, 10)) > 0); ++i)
				{
					sscanf(buf3, "%d,", &i);
					printf("child3: read(%d) %s\n", rn3, buf3);
					memset(buf3, 0, 10);
					sum += i;
				}
				printf("child3: sum = %d\n", sum);
				close(fd2[0]);
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
		close(fd1[1]);close(fd1[0]);close(fd2[1]);close(fd2[0]);
		exit(0);
	}
}
