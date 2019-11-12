#include <unistd.h>
#include <stdio.h>
int main(void)
{
	pid_t pid;
	int count=0;
	printf("0000 pid=%d\n",getpid());
	pid=vfork();
	if(pid==0)
	{
		printf("1111 pid=%d\n",getpid());
		printf("count= %d\n",count);
	}
	else
	{
		printf("2222 pid=%d\n",getpid());
		printf("count= %d\n",count);
	}
 
	return 0;
}
