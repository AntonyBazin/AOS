#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	printf("I am father before fork. My PID is %d, my PPID is %d, my PGID is %d\n",
		getpid(), getppid(), getpgid(getpid()));
	if (fork()) {
		printf("I am father after fork. My PID is %d PPID is %d, my PGID is %d\n",
			getpid(), getppid(), getpgid(getpid()));
		sleep(1);
		printf("I am father. I was waiting for son to terminate.\n");
		system ("ps -f");
		exit(0);
	}
	else {
		printf("I am son. I exit with code 2\n");
		exit(2);
	}
}
