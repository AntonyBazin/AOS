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
	signal(SIGINT, sighandler);
	if((pid = fork())){
		sleep(1);
		printf("Sending to child signal %d\n", SIGINT);
		kill(pid, SIGINT);
		wait_code = wait(&return_code);
		if (WIFSIGNALED(return_code))
			printf("Child was stopped by %d\n", WTERMSIG(return_code));

		printf("Child exited with %d\n", return_code);
		printf("Got %d from wait\n", wait_code);
		printf("Set errno: %d\n", errno);
	} else {
		printf("I am son. My pid is %d, my ppid is %d\n", getpid(), getppid());
		printf("Set errno: %d\n", errno);
		for (int i = 0; i < 100; ++i) {
			for (int j = 0; j < 3000; ++j)
				for (int k = 0; k < 3000; ++k);
			printf("Outer: %d\n", i);
		}
		printf("Set errno: %d\n", errno); // interrupted system call (pause)
	}
	return 0;
}

void sighandler(int signum){
	printf("This is my custom handler.\n");
	signal(signum, SIG_DFL);
}