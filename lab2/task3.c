#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>


int main(){
	int rc, ret_code;
	printf("I am father before fork. My PID is %d, my PPID is %d, my PGID is %d\n",
		getpid(), getppid(), getpgid(getpid()));
	printf("I am father. Syscall \"wait\" returned %d\n", wait(&rc));
	if (fork()) {
		printf("I am father after fork. My PID is %d PPID is %d, my PGID is %d\n",
			getpid(), getppid(), getpgid(getpid()));
		ret_code = wait(&rc);
		sleep(1);
		printf("I am father. I was WAITing for son to terminate with code %d.\n", ret_code);
		system ("ps -uf");
		exit(0);
	}
	else {
		printf("I am son after fork. My PID is %d PPID is %d, my PGID is %d\n",
					getpid(), getppid(), getpgid(getpid()));
		printf("I am son. I exit with code 2\n");
		exit(2);
	}
}
