/*
	如启用添加标志打开一文件以便读、写，能否用lseek在任一位置开始读？
	能否用lseek更新文件中任一部分的数据？请写一段程序以验证之。
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	int fd, i;
	char buf[10] = "";
	char buf2[10] = "0123456789";

	if((fd = open("3-6.txt", O_RDWR | O_APPEND)) < 0)
		printf("open error");

	if(lseek(fd, 40, SEEK_SET) == -1)
		printf("lseek error");

	if(read(fd, buf, 10) != 10)
		printf("read error");

	for(i = 0; i < 10; i++)
	{
		printf("%c", buf[i]);
	}

	if(write(fd, buf2, 10) != 10)
		printf("write error");

	return 0;
}
