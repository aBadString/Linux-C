#include "my.h"

int main()
{
	int pid =fork();
	if(pid < 0)
	{
		perror("failed to fork!\n");
		return -1;
	}
	else if(pid == 0)
	{
		printf("%d : child is exit now!\n",getpid());
		exit(0);
	}
	else
	{
		printf("%d : parent is running!\n",getpid());
		while(1) continue;
		exit(0);
	}
}

