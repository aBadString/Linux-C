#include "my.h"

int g = 1;

int main()
{
	int local = 1;
	int *m = malloc(sizeof(int));
	*m = 1;
	
	pid_t pid = fork();
	if(pid < 0)
	{
		printf("fork failed (%s)\n", strerror(errno));
		return 1;
	}
	else if(pid == 0)
	{
		local = 9999;
		g = 9999;
		*m = 9999;
		fprintf(stderr, "[child] child change local global malloc value to 9999\n");
		free(m);
		sleep(10);
		fprintf(stderr, "[child] exit!\n");
		exit(0);
	}
	else
	{
		fprintf(stderr, "[parent] parent wating child exit!\n");
		waitpid(pid, NULL, 0);
		fprintf(stderr, "[parent] child have exit!\n");
		fprintf(stderr, "[parent] g=%d\n", g);
		fprintf(stderr, "[parent] local=%d\n", local);
		fprintf(stderr, "[parent] m=%d\n", *m);
	}
}
