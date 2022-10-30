#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>


extern int errno;
/*
If the child process for which status was returned 
by the wait or waitpid function exited because it 
raised a signal that caused it to exit, the WIFSIGNALED
macro evaluates to TRUE and the WTERMSIG macro can be
used to determine which signal was raised by the child process.
Otherwise, the WIFSIGNALED macro evaluates to FALSE.
*/

int main(void){
	int pid;
	int return_code;
	int wait_code;
	if((pid = fork())){
		sleep(1);
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
		for (int i = 0; i < 100; ++i) {
			for (int j = 0; j < 3000; ++j)
				for (int k = 0; k < 3000; ++k);
			printf("Outer: %d\n", i);
		}
	}
	return 0;
}