#ifndef _UHEAD_H
#define _UHEAD_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define LEN 100
#define BUFFER_SIZE 64

struct arg
{
	int sum;
	float avg;
};

int usum(int*, int);
void urand(int*, int);
void show(int*, int);
struct arg operate(int*, int);
void bsort(void*, size_t, size_t, int (*)(const void*, const void*));
int compar(const void*, const void*);
void sysbsort(int *, int);
void sysqsort(int *, int);
int writedate(int*, int, const char*);
int showfile(const char*);

#endif
