#include "lib.h"
#include <stdio.h>

#define LEN 10

int main()
{
	int arr[LEN];

	urand(arr, LEN);
	printf("sum=%d\n", sum(arr, LEN));
	printf("max=%d\n", max(arr, LEN));
}
