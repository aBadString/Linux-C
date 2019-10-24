#include <stdio.h>
int main(int argc, char *argv[])
{
	int i, res;

	res = printf("hello");
	for(i=0;i<=1024-res;i++)
	{
		putchar('\0');
	}
	while(1);
}
