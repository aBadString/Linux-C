#include "uhead.h"

struct arg operate(int* arr, int len)
{
	struct arg res;
	res.sum = usum(arr, len);
	res.avg = ((float)res.sum) / ((float)len);

	return res;
}

void bsort(void* base, size_t num, size_t width, int (*compar)(const void*, const void*))
{
    
	void* temp = malloc(width);
	int i, j;
	
    for (i = 0; i < num-1; i++)
	{
        for (j = 0; j < num-1-i; j++)
		{
            if (compar(base + width*j, base + width*(j+1)) > 0)
			{
				memcpy(temp, base + width*(j+1), width);
  				memcpy(base + width*(j+1), base + width*j, width);
				memcpy(base + width*j, temp, width);
            }
        }
    }
	free(temp);

	return;
}

int compar(const void* a, const void* b)
{
	int aa = *((int*)a);
	int bb = *((int*)b);
	if(aa == bb)
	{
		return 0;
	}
	else if(aa > bb)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

void sysbsort(int *arr, int n)
{
	struct timeval tv1, tv2;

	gettimeofday(&tv1, NULL);
	bsort((void*)arr, n, sizeof(int), compar);
	gettimeofday(&tv2, NULL);
	printf("bsort spend %ld us:\n", tv2.tv_usec - tv1.tv_usec);
}

void sysqsort(int *arr, int n)
{
	struct timeval tv1, tv2;

	gettimeofday(&tv1, NULL);
	qsort((void*)arr, n, sizeof(int), compar);
	gettimeofday(&tv2, NULL);
	printf("qsort spend %ld us:\n", tv2.tv_usec - tv1.tv_usec);
}
