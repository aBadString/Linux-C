#include "my.h"

int main()
{
	pid_t p;
	int fd[2];
	char buf[1];
	
	pipe(fd);
	p = fork();
	if(p < 0)
	{
		perror("fork failed.\n");
		return -1;
	}
	else if(p == 0)
	{
		char b = 'a';
		close(fd[0]);
		for(int i = 0; i < 65537; ++i) // 65536 65537
		{
			write(fd[1], &b, sizeof(b));
			if(i > 65530)
			{
				printf("child write %d times\n", i+1);
			}
		}
		printf("child write ok.\n");
		close(fd[1]);
		exit(0);
	}
	else
	{
		close(fd[1]);
		wait(NULL);
		for(int i = 0; i < 65536; ++i)
		{
			read(fd[0], buf, 1);
			if(i < 10)
			{
				printf("parent read %d times, that is %s\n", i+1, buf);
			}
		}
		close(fd[0]);
		exit(0);
	}
}
