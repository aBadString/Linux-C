#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int globa = 4;
int main()
{
	pid_t pid;
	int vari = 5;
	
	printf("before fork\n");
	if((pid = fork()) < 0)
	{
		printf("fork error\n");
		exit(0);
	}
	// fork 返回给子进程0;
	// 返回给父进程一个大于0的pid号;
	else if(pid == 0)
	{
		globa++;
		vari--;
		printf("Child changed\n");
	}
	else
	{
		printf("Parent did not changed\n");
	}
	printf("globa=%d vari=%d\n", globa, vari);
	exit(0);
}
