#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[],char *env[])
{
	int i;
	extern char **environ;

	for(i=0; env[i]; i++)
	{
		printf("%s\n",env[i]);
	}
	
	for(i=0; environ[i]; i++)
	{
		printf("%s\n",environ[i]);
	}
	
	printf("%s\n", getenv("PATH"));
	
	return 0;
}
