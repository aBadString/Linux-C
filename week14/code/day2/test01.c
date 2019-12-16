#include "my.h"

int i = 0;

void foo()
{
	int buffer[256];
	i++;
	printf("%d : call.\n", i);
	foo();
}

int main()
{
	foo();
	return 0;
}
