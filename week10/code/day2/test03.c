#include "my.h"

int g = 10;
int main()
{
	int s = 20;
	static int k = 30;
	extern int out;
	
	//pid_t pid = fork();
	pid_t pid = vfork();
	if(pid < 0)
	{
		perror("failed vfork!\n");
		exit(-1);
	}
	else if(pid == 0)
	{
		printf("child: pid=%d, &g=%16p, &k=%16p, &s=%16p, &out=%16p\n", getpid(), &g, &k, &s, &out);
		g = 100;
		k = 100;
		s = 100;
		//out = 100;
		printf("child: pid=%d, g=%d, k=%d, s=%d, out=%d\n", getpid(), g, k, s, out);
		out = 100;
		_exit(0);
	}
	else
	{
		g = 200;
		k = 200;
		s = 200;
		//out = 200;
		printf("parent: pid=%d, &g=%16p, &k=%16p, &s=%16p, &out=%16p\n", getpid(), &g, &k, &s, &out);
		printf("parent: pid=%d, g=%d, k=%d, s=%d, out=%d\n", getpid(), g, k, s, out);
		return 0;
	}
}
