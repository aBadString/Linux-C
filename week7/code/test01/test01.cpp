#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

int main()
{
	int fd;
	FILE *file;
	char *s = "hello,world\n";
	
	if((fd=open("test1.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) == -1)
	{
		cout << "Error open file test1.txt" << endl;
		return -1;
	}
	if((file = fopen("test2.txt", "w+")) == NULL)
	{
		cout << "Error open file test2.txt" << endl;
		return -1;
	}
	cout << "File has been opened" << endl;
	sleep(15);

	if(write(fd, s, strlen(s)) < strlen(s))
	{
		cout << "Write Error in test1.txt" << endl;
		return -1;
	}
	if(fwrite(s, sizeof(char), strlen(s), file) < strlen(s))
	{
		cout << "Write Error in test2.txt" << endl;
		return -1;
	}
	cout << "After write" << endl;
	sleep(15);
	cout << "After sleep" << endl;

	close(fd);
	return 0;
}
