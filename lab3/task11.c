#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void sighandler(int signum){
	printf("My pid is %d, I intercepted ", getpid());
	printf("signal %d\n", signum);
}


int main() {
	int pid;
	sigset_t to_block, empty;
	sigemptyset(&to_block);
	sigemptyset(&empty);

	sigaddset(&to_block, SIGUSR1);	
	sigprocmask(SIG_BLOCK, &to_block, NULL);
	printf("My pid is %d\n", getpid());

	if((pid = fork())){
		signal(SIGUSR2, sighandler);
		printf("Father starts\n");
		sleep(2);
		printf("Father kills son with SIGUSR1\n");
		kill(pid, SIGUSR1);
		sigemptyset(&empty);
		sigsuspend(&empty);
		sigprocmask(SIG_BLOCK, &to_block, NULL);
		printf("Father works\n");
		sleep(4);
		printf("Father kills son with SIGUSR1 again\n");
		kill(pid, SIGUSR1);
		sigemptyset(&empty);
		//sigsuspend(&empty);
	} else {
		printf("I am son. My pid is %d, my ppid is %d\n", getpid(), getppid());
		signal(SIGUSR1, sighandler);
		printf("Child starts\n");
		sleep(4);
		printf("Child kills father with SIGUSR2\n");
		kill(getppid(), SIGUSR2);
		sigemptyset(&empty);
		sigsuspend(&empty);
		sigprocmask(SIG_BLOCK, &to_block, NULL);
		printf("Child works\n");
		sleep(2);
		printf("Child kills father with SIGUSR2 again\n");
		kill(getppid(), SIGUSR2);
		sigemptyset(&empty);
		sigsuspend(&empty);
		exit(0);
	}
	
	return 0;
}
