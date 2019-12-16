#include "my.h"

enum command {QUIT = 0, WORK};

struct thread
{
	int no;
	enum command cmd;
};

void thread_func(struct thread * p)
{
	printf("\nThread %d create with commandnumber %d is running\n", p->no, p->cmd);
	sleep(p->cmd);
	printf("\nThread %d finish now\n", p->no);
	pthread_exit(NULL);
}
enum command get_usr_cmd()
{
	int cmd;
	printf("please enter a command number(0-9): ");
	scanf("%d", &cmd);
	getchar();
	return (enum command)cmd;
}

int main(void)
{
	pthread_t tid;
	int rv, cmd, k = 0;
	struct thread *last_thread, *tp;
	
	while(1)
	{
		cmd = get_usr_cmd();
		if(cmd == QUIT)
		{
			printf("initial thread will finish soon\n");
			pthread_exit(NULL);
		}
		
		tp = (struct thread *)malloc(sizeof(struct thread));
		tp->no = k++;
		tp->cmd = cmd;
		
		rv = pthread_create(&tid, NULL, (void *(*)())thread_func, (void *)tp);
		check_error(rv, "pthread_create()");
		printf("Creade thread %d\n", tp->no);
		rv = pthread_detach(tid);
		check_error(rv, "pthread_detach()");
	}
}
