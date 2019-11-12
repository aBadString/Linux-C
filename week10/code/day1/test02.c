#include "my.h"

int g = 88;
int main()
{
	int v = 99;
	pid_t pid;
	pid = vfork();
	if(pid < 0)
	{
		perror("vfork failed");
		exit(-1);
	}
	else if(pid == 0)
	{
		g++;
		v++;
		printf("child: pid=%d, g=%d, v=%d\n", getpid(), g, v);
		//_exit(0);
		//exit(0);
		return 0;
	}
	else
	{
		printf("return value = %d\n", pid);
		printf("parent: pid=%d, g=%d, v=%d\n", getpid(), g, v);
		return 0;
	}
}
