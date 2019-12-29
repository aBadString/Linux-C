// 客户端
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stddef.h>
#include <time.h>
#define SERVPORT 3333
#define MAXDATASIZE 20 /*每次最大数据传输量 */

int getIP(char *str)
{
	int i = 0;
	char host_name[10] = "localhost";
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
		sprintf(str,"%s", inet_ntoa(*(struct in_addr*)hptr->h_addr_list[i]));
	}
	
	return 0;
}

int main(int argc, char *argv[]){
	int sockfd, recvbytes;
	char buf[MAXDATASIZE];
	char ip[16];
	time_t timep;
	char info[128];
	
	struct hostent *host;
	struct sockaddr_in serv_addr;
	
	if (argc < 2) {
		fprintf(stderr,"Please enter the server's hostname!\n");
		exit(1);
	}
	if((host=gethostbyname(argv[1]))==NULL) {
		herror("gethostbyname error！");
		exit(1);
	}
	
	// 1. 建立socket sockfd
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("socket create error！");
		exit(1);
	}
	
	// 下面四个语句初始化 serv_addr
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(SERVPORT);
	serv_addr.sin_addr = *((struct in_addr *)host->h_addr);
	bzero(&(serv_addr.sin_zero),8);
	// 2. 请求连接connect
	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)) == -1) {
		perror("connect error！");
		exit(1);
	}
	
	// 获取本机IP和时间
    getIP(ip);
	time(&timep);
	sprintf(info, "IP: %s, Time: %s",ip, ctime(&timep));
	//sleep(10);
	// 3. 发送数据send
	if (send(sockfd, info, strlen(info), 0) == -1)
	{
		perror("send 出错！");
	}
	
	// 4. 接收数据recv
	while ((recvbytes=recv(sockfd, buf, MAXDATASIZE, 0)) == 0) {
		continue;
	}
	buf[recvbytes] = '\0';
	printf("收到: %s",buf);
	
	sleep(1);
	// 5. 发送quit
	if (send(sockfd, "quit", strlen(info), 0) == -1)
	{
		perror("send 出错！");
	}
	
	// 6. 关闭close
	close(sockfd);
}
