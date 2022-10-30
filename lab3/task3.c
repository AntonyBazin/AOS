#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>


void sighandler(int signum){
    int return_code;
    wait(&return_code);
	printf("Child exited with %d.\n", return_code);
    //system("ps -uf");
    //signal(signum, SIG_DFL);
}

int main(void){
	int children[7];
	for(int i = 0; i < 7; ++i){
        if(!(children[i] = fork())){
            printf("I am son. My pid is %d, my ppid is %d\n", getpid(), getppid());
            sleep(i);
            printf("Child exits with code 0\n");
            exit(0);
        }
    }

	signal(SIGCHLD, sighandler);
    while(1){
        printf("Parent loop...\n");
        sleep(1);
    }
	return 0;
}