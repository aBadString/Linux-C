#include "my.h"

int main()
{
	int fd;
	pid_t pid;
	char buf[4];
	
	memset(buf, 0, 4);
	if((fd = open("read.txt",O_RDONLY)) < 0)
	{
		fprintf(stderr, "failed to open, reason(%s)\n", strerror(errno));
	}
	
	pid = fork();
	if(pid < 0)
	{
		perror("failed fork!\n");
		exit(-1);
	}
	else if(pid == 0) // child
	{
		while(read(fd, buf, 2) > 0)
		{
			printf(" child(%d): %s", getpid(), buf);
			memset(buf, 0, 4);
			sleep(1);
		}
		close(fd);
		_exit(0);
	}
	else // parent
	{
		while(read(fd, buf, 2) > 0)
		{
			printf("parent(%d): %s", getpid(), buf);
			memset(buf, 0, 4);
			sleep(1);
		}
		close(fd);
		_exit(0);
	}
}
