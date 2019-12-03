#include "my.h"

int sig_handler(int signo, siginfo_t *info, void *context)
{
	printf("\nget signal: %d\n", signo);
	printf("signal number is %d\n", info->si_signo);
	printf("pid = %d\n", getpid());
	printf("sigval = %d\n", info->si_value.sival_int);
}

int main()
{
	struct sigaction new;
	
	printf("pid = %d\n", getpid());
	
	sigemptyset(&new.sa_mask);
	new.sa_sigaction = sig_handler;
	new.sa_flags |= SA_SIGINFO | SA_RESTART;
	
	if(sigaction(36, &new, NULL) == -1)
	{
		perror("set failed.\n");
		exit(1);
	}
	
	while(1)
	{
		pause();
	}
	printf("Done!\n");
	exit(0);
}
