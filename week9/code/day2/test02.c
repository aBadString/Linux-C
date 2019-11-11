#include "my.h"
#include <string.h>

static void mem_leak1()
{
	char *p = malloc(1);
}

static void mem_leak2()
{
	FILE *fp = fopen("test02.txt", "w");
}

static void mem_overrun1()
{
	char *p = malloc(1);
	*(short*)p = 2;
	free(p);
}

static void mem_overrun2()
{
	char arr[5];
	strcpy(arr, "hello");
}

static void mem_double_free()
{
	char *p = malloc(1);
	free(p);
	free(p);
}

static void mem_free_wild_pointer()
{
	char *p;
	free(p);
}

int main()
{
	mem_leak1();
	mem_leak2();
	mem_overrun1();
	mem_overrun2();
	mem_double_free();
	mem_free_wild_pointer();
}
