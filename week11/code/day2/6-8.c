#include <stdio.h>
#include <time.h>
#include "my.h"

void init_daemon(void);

int main()
{
	FILE *fp;
	time_t t;
	
	init_daemon();
	while(1)
	{
		sleep(10);
		if((fp = fopen("6-8.log", "a")) >= 0)
		{
			t = time(0);
			fprintf(fp, "守护进程还在运行, 时间是: %s", asctime(localtime(&t)));
			fclose(fp);
		}
	}
}
