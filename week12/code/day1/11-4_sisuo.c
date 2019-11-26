#include "my.h"

int main()
{
	pid_t p;
	char w_buf[100], r_buf[100];
	int fd[2], wn, rn;
	
	memset(w_buf, 0, 100);
	memset(r_buf, 0, 100);
	pipe(fd);
	p = fork();
	if(p < 0)
	{
		perror("fork failed.\n");
		return -1;
	}
	else if(p == 0)
	{
		close(fd[0]);
		printf("child pid = %d\n", getpid());
		
		/*sprintf(w_buf, "child is running. pid = %d", getpid());
		if((wn = write(fd[1], w_buf, sizeof(w_buf))) < 0)
		{
			printf("write failed.\n");
			exit(-1);
		}*/
		printf("child write to pipe %d byte.\n", wn);
		close(fd[1]);
		exit(0);
	}
	else
	{
		close(fd[1]);
		wait(NULL);
		while((rn = read(fd[0], r_buf, sizeof(r_buf))) <= 0)
		{
			printf("parent read failed.\n");
			sleep(1);
		}
		printf("parent read from pipe total = %d, content = %s \n", rn, r_buf);
		close(fd[0]);
		exit(0);
	}
}
