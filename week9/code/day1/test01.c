#include <stdio.h>
#include <stdlib.h>

static void __attribute__ ((constructor)) before_main(void)
{
	printf("Running befored main!\n");
}

int main()
{
	printf("main!\n");
	return 0;
}
