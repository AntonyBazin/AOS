#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>


extern int errno;

/*
Alarms  created  by  alarm() are preserved across execve(2) and 
are not inherited by children created via fork(2).
*/
void sighandler(int);


int main(void){
	int pid;
	int return_code;
	int wait_code;
	signal(SIGALRM, sighandler);
	if((pid = fork())){
		printf("Sending to child signal %d\n", SIGUSR1);
		kill(pid, SIGUSR1);
		wait_code = wait(&return_code);
		if (WIFSIGNALED(return_code))
			printf("Child was stopped by %d\n", WTERMSIG(return_code));

		printf("Child exited with %d\n", return_code);
		printf("Got %d from wait\n", wait_code);
		printf("Set errno: %d\n", errno);
	} else {
		printf("I am son. My pid is %d, my ppid is %d\n", getpid(), getppid());
		pause();
		printf("Set errno: %d\n", errno); // interrupted system call (pause)
	}
	return 0;
}

void sighandler(int signum){
	printf("This is my custom handler.\n");
	signal(signum, SIG_DFL);
}