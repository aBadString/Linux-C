#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFSIZE 8192

int main()
{
	int n;
	char buf[BUFFSIZE];
	while((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
	{
		if(write(STDOUT_FILENO, buf, n) != n)
		{
			printf("write error");
			exit(-1);
		}
	}
	if(n < 0)
	{
		printf("read error");
		exit(-2);
	}
	exit(0);
}
