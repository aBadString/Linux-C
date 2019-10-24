#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#define LEN 10

int main()
{
	int arr[LEN];
	void *handle;
	void (*urand)(), (*show)();
	int (*sum)(), (*max)();
	char *error;

	handle = dlopen("/home/rlk/Desktop/Test/week6/dyamiclib/libdynamic.so", RTLD_LAZY);
	if(!handle)
	{
		fprintf(stderr, "%s\n", dlerror());
		exit(1);
	}

	urand = dlsym(handle, "urand");
	if((error = dlerror()) != NULL)
	{
		fprintf(stderr, "%s\n", dlerror());
		exit(1);
	}
	show = dlsym(handle, "show");
	if((error = dlerror()) != NULL)
	{
		fprintf(stderr, "%s\n", dlerror());
		exit(1);
	}
	max = dlsym(handle, "max");
	if((error = dlerror()) != NULL)
	{
		fprintf(stderr, "%s\n", dlerror());
		exit(1);
	}
	sum = dlsym(handle, "sum");
	if((error = dlerror()) != NULL)
	{
		fprintf(stderr, "%s\n", dlerror());
		exit(1);
	}

	urand(arr, LEN);
	show(arr, LEN);
	printf("sum=%d\n", sum(arr, LEN));
	printf("max=%d\n", max(arr, LEN));

	if(dlclose(handle) < 0)
	{
		fprintf(stderr, "%s\n", dlerror());
		exit(1);
	}

	return 0;
}
