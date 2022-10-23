#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

/*
?
*/


int main(){
	printf("I am father before fork. My PID is %d, my PPID is %d, my PGID is %d\n",
		getpid(), getppid(), getpgid(getpid()));
	if (fork()) {
		printf("I am father after fork. My PID is %d PPID is %d, my PGID is %d\n",
			getpid(), getppid(), getpgid(getpid()));
		pause();
		printf("I am father after pause().\n");
		exit(0);
	}
	else {
		printf("I am son after fork. My PID is %d PPID is %d, my PGID is %d\n",
					getpid(), getppid(), getpgid(getpid()));
		setpgrp();
		pause();
		printf("I am son after pause. I exit with code 2.\n");
		exit(2);
	}
}
