#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


int main(){
	printf("I am father before fork. My pid is %d, my ppid is %d\n", getpid(), getppid());
	if (fork()){
		printf("I am father after fork. My pid is %d, my ppid is %d\n", getpid(), getppid());
		wait(NULL);
		exit(0);
	}
	else{
		printf("I am son. My pid is %d, my ppid is %d\n", getpid(), getppid());
		exit(0);
	}
}
