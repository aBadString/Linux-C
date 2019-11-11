#include "my.h"

int x = 100;
int main(int argc, int *argv[])
{
	int y = 0;
	static int w = 33;
	
	printf("test02: pid=%d, ppid=%d\n", getpid(), getppid());
	for(int i=0; i < argc; i++)
	{
		printf("%d : %s\n", i, argv[i]);
	}
	
	printf("test02: address x=%ld, y=%ld, w=%ld\n", &x, &y, &w);
	
	//sleep(50);
	return 0;
}

