#include <stdio.h>

int main()
{
	int sum = 0;
	for(int i = 0; i < 65536; i++)
	{
		sum += i;
	}
	printf("%d", sum);
}
