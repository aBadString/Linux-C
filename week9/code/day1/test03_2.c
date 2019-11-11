#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int glob = 6;
int main()
{
	int var;
	int pid;
	var = 88;
 
	printf("father:\n");
	printf("&glob = %p\n",&glob);
	printf("&var = %p\n",&var);
	printf("__________________________________\n");
	if((pid = fork()) < 0)
	{
		perror("fail to fork");
		return -1;
 	}
 	else if(pid == 0)
 	{
		printf("child var value not change\n:");
		printf("&glob = %p\n",&glob);
		printf("&var = %p\n",&var);
		glob ++;
		var ++;
		printf("__________________________________\n");
		printf("child var value change:\n");
		printf("&glob = %p\n",&glob);
		printf("&var = %p\n",&var);
	}
	exit(0);
}
