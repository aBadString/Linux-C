#include "my.h"

int main()
{
	char *args[] = {"./test02.out","a", "b", "c", "d", NULL};
	printf("caller02: pid=%d, ppid=%d\n", getpid(), getppid());
	execvp("test02.out", args);
	printf("after calling\n");
	
	//sleep(50);
	return 0;
}
