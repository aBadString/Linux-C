#include "my.h"

int main()
{
	printf("caller02: pid=%d, ppid=%d\n", getpid(), getppid());
	execl("./test02.out", "a", "b", "c", "d", NULL);
	printf("after calling\n");
	
	//sleep(50);
	return 0;
}
