#include "my.h"

static void fun1(void)
{
	printf("invoked callbankfun!\n");
}

int main()
{
	atexit(fun1);
    FILE *fp; 
    char buf[]="buffer data!";
    if((fp=fopen("test01.dat","w+"))==NULL)
    {
       perror("create file failed!\n");
       exit(-1);
    }
    if(fputs(buf,fp)==EOF)
    {
       perror("fputs file failed!\n");
       exit(-1);
    }
	printf("hello   ");
	exit(0);

	//_exit(1);
	//exit(1);
}
