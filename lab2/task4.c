#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>


int main(){
	//int p, rc;
	printf("I am father before fork. My PID is %d, my PPID is %d, my PGID is %d\n",
		getpid(), getppid(), getpgid(getpid()));
	if (fork()) {
		printf("I am father after fork. My PID is %d PPID is %d, my PGID is %d\n",
			getpid(), getppid(), getpgid(getpid()));
		system ("ps -uf");
		printf("I am father. I exit with code 0.\n\n");
		exit(0);
	}
	else {
		printf("I am son after fork. My PID is %d PPID is %d, my PGID is %d\n",
					getpid(), getppid(), getpgid(getpid()));
		sleep(2);
		printf("I am son. I was waiting for father to terminate.\n");
		printf("I am son. My PID is %d PPID is %d, my PGID is %d\n",
							getpid(), getppid(), getpgid(getpid()));
		system ("ps -uf");
		printf("\n");
		exit(0);
	}
}
