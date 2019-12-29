#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#include<errno.h>  
#include<sys/types.h>  
#include<sys/socket.h>  
#include<netinet/in.h>  
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define DEFAULT_PORT 3333
#define MAXLINE 4096  
int main(int argc, char** argv)  
{  
    int socket_fd, connect_fd;  
    struct sockaddr_in     servaddr;  
    char buff[128]; 
    //char log[128];
    int n;  
    FILE *file;
    
    //初始化Socket  
    if( (socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){  
    printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);  
    exit(0);  
    }  
    //初始化  
    memset(&servaddr, 0, sizeof(servaddr));  
    servaddr.sin_family = AF_INET;  
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);//IP地址设置成INADDR_ANY,让系统自动获取本机的IP地址。  
    servaddr.sin_port = htons(DEFAULT_PORT);//设置的端口为DEFAULT_PORT  
  
    //将本地地址绑定到所创建的套接字上  
    if( bind(socket_fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1){  
    printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);  
    exit(0);  
    }  
    //开始监听是否有客户端连接  
    if( listen(socket_fd, 10) == -1){  
    printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);  
    exit(0);  
    }  
    printf("======running======\n");  
    while(1){
		memset(buff,0,MAXLINE);
		
		// select
		struct timeval tv;
		fd_set readfds;
		tv.tv_sec = 1;
		tv.tv_usec = 500000;
		FD_ZERO(&readfds);
		FD_SET(socket_fd, &readfds);
		int ret = select(socket_fd+1, &readfds, NULL, NULL, &tv);
		if(ret == 0)
		{
			continue;
		}
		if (ret < 0)
		{
			perror("select error: ");
			exit(-1);
		}
		
		/*
		//阻塞直到有客户端连接  
        if( (connect_fd = accept(socket_fd, (struct sockaddr*)NULL, NULL)) == -1){  
			if (FD_ISSET(socket_fd, &readfd
			printf("accept socket error: %s(errno: %d)",strerror(errno),errno);  
			continue;  
		}
		*/
		
		if( (connect_fd = accept(socket_fd, (struct sockaddr*)NULL, NULL)) == -1){  
					printf("accept socket error: %s(errno: %d)",strerror(errno),errno);  
					}
		//接受客户端传过来的数据		
		if(!fork())
		{
		
			if (FD_ISSET(socket_fd, &readfds))
			{
				printf("child pid:%d connect_fd: %d\n", getpid(), connect_fd);
				
				n = recv(connect_fd, buff, MAXLINE, 0);
				buff[n] = '\0';

				//memset(log, 0, sizeof(log));
				//sprintf(log, "client. IP: %s, Time: \n", buff);
				
				// 写入日志
				printf("收到: %s", buff);
				if((file = fopen("server.txt", "a+")) != NULL)
				{
					fwrite(buff, 128, 1, file);
				}
				fclose(file);
				sleep(2);
				
				//向客户端发送回应数据  
				if(send(connect_fd, "Hello!\n", 7,0) == -1)  {
					perror("send error");
				}
				
				// 4. 接收数据recv
				while (recv(connect_fd, buff, MAXLINE, 0) == 0) {
					continue;
				}
				close(connect_fd);
			}
			else
			{
				printf("time out!!");
			}
			
			printf("child pid:%d quit\n", getpid());
			exit(0);
		}
    }
	close(socket_fd);
}
