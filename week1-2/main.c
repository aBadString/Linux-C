#include "uhead.h"

int main()
{
	int arr[LEN];
	struct arg res;

	urand(arr, LEN);
	show(arr, LEN);

	writedate(arr, LEN, "org.txt");
	
	sysbsort(arr, LEN);
	show(arr, LEN);
	
	sysqsort(arr, LEN);
	show(arr, LEN);

	writedate(arr, LEN, "sort.txt");
	
	res = operate(arr, LEN);
	printf("%d\t%f\n", res.sum, res.avg);

	showfile("org.txt");
	showfile("sort.txt");

	return 0;
}
