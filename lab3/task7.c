#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>


extern int errno;

// Answer: to use signals and signal handlers.
/*
pause() causes the calling process (or thread) to sleep until a
signal is delivered that either terminates the process or causes
the invocation of a signal-catching function.
*/
void sighandler(int);


int main(void){
	int pid;
	int return_code;
	int wait_code;
	signal(SIGUSR1, sighandler);
	if((pid = fork())){
		sleep(1);
		printf("Sending to child signal %d\n", SIGUSR1);
		kill(pid, SIGUSR1);
		wait_code = wait(&return_code);
		if (WIFSIGNALED(return_code))
			printf("Child was stopped by %d\n", WTERMSIG(return_code));

		printf("Chiled exited with %d\n", return_code);
		printf("Got %d from wait\n", wait_code);
		printf("Set errno: %d\n", errno);
	} else {
		printf("I am son. My pid is %d, my ppid is %d\n", getpid(), getppid());
		pause();
	}
	return 0;
}

void sighandler(int signum){
	printf("This is my custom handler.\n");
	signal(signum, SIG_DFL);
}