#include <stdio.h>
#include <malloc.h>

int a;
static int b = 10;

int main(int argc, char *argv[], char *envp[])
{
	int a = 10;
	char *p = (char*)malloc(sizeof(char));
	
	printf("a=%d, p=0x%x\n", a, p);
	
	return 0;
}
