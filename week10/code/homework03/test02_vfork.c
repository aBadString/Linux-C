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
	
	//pid = fork();
	pid = vfork();
	if(pid < 0)
	{
		perror("failed fork!\n");
		exit(-1);
	}
	else if(pid == 0) // child
	{
		int i = 10;
		while(i-->0)
		{
			if(read(fd, buf, 2) > 0)
				printf(" child(%d): %s", getpid(), buf);
			else
				printf(" child(%d): NULL", getpid());
			memset(buf, 0, 4);
			sleep(1);
		}
		close(fd);
		_exit(0);
	}
	else // parent
	{
		int j = 10;
		while(j-->0)
		{
			if(read(fd, buf, 2) > 0)
				printf("parent(%d): %s", getpid(), buf);
			else
				printf("parent(%d): NULL", getpid());
			memset(buf, 0, 4);
			sleep(1);
		}
		close(fd);
		_exit(0);
	}
}
