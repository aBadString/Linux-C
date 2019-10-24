#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main()
{
	int fd;
	if((fd = creat("file.hole", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
		printf("creat error");

	if(write(fd, buf1, 10) != 10)
		printf("buf1 write error");
	/* offset = 10 */

	if(lseek(fd, 40, SEEK_SET) == -1)
			printf("lseek error");
		/* offset = 40 */
	
	if(write(fd, buf2, 10) != 10)
		printf("buf2 write error");
	/* offset = 50 */

	exit(0);
}
