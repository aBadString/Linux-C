#include "my.h"

int main()
{
	int ret;
	
	printf("caller02: pid=%d, ppid=%d\n", getpid(), getppid());
	ret = system("./test02.out a b c d");
	printf("after calling\n");
	
	sleep(50);
	return 0;
}

