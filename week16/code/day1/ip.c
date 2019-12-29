#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stddef.h>
#include <time.h>
 
 
 
void getIP(char *str)
{
	int i = 0;
	char host_name[128] = "localhost";
    struct hostent *hptr;
 
    if (gethostname(host_name, sizeof(host_name)) < 0)
	{
		printf("gethostname error\n");
		return -1;
	}
    if ((hptr=gethostbyname(host_name)) == NULL)
	{
		printf("gethostbyname error\n");
		return -1;
	}
	for( i = 0; hptr->h_addr_list[i] != NULL; i++)
	{
		sprintf(str, inet_ntoa(*(struct in_addr*)hptr->h_addr_list[i]));
	}
}

/*
void getNowTime(char *time)
{
	 timespec time;
	 clock_gettime(CLOCK_REALTIME, &time); //获取相对于1970到现在的秒数
	 tm nowTime;
	 localtime_r(&time.tv_sec, &nowtime);
	 sprintf(time, "%04d%02d%02d%02d:%02d:%02d", nowTime.tm_year + 1900, nowTime.tm_mon, nowTime.tm_mday, 
	  nowTime.tm_hour, nowTime.tm_min, nowTime.tm_sec);
}*/

// 获取本地IP时，一般都是127.0.0.1
int main(int argc, const char **argv)
{
    char str[20];
    char time[20];
    getIP(str);
    //getNowTime(&time);
    printf("IP: %s. Time: %s\n", str, time);
    
    return 0;
}
