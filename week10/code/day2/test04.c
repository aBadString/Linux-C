#include "my.h"

int g = 10;
char a[100] = {0};

int main(int argc, char *argv[])
{
	pid_t pid;
	int i;
	static int k = 20;
	
	printf("test04: pid=%d\n&g=%16p\n&k=%16p\n&a=%16p\n", getpid(), &g, &k, a);
	for(i=0; i < 10; i++)
	{
		printf("test04: g=%d, k=%d\n", g++, k++);
	}
	return 0;
}
