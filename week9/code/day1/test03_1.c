#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int glob = 6;
char buf[] = "a write to stdout\n";
	
int main()
{
	int var;
	int pid;
	var = 88;
	if(write(STDOUT_FILENO,buf,sizeof(buf) -1) != sizeof(buf) -1)
	{
		perror("fail to write");
		return -1;
	}
	printf("before fork\n");
	if((pid = fork()) < 0)
	{
		perror("fail to fork");
		return -1;
	}
	else if(pid == 0)
	{
		glob ++;
		var ++;
	}
	else
	{
		sleep(2);
	}
	printf("pid = %d,glob = %d,var = %d\n",getpid(),glob,var);
	exit(0);
}
