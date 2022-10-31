#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>


// When you create a new process, it inherits its parent's mask.
void sighandler(int);


int main(){
	sigset_t sigset;
    signal(SIGINT, sighandler);
	if ((sigemptyset(&sigset) == -1) || (sigaddset(&sigset, SIGINT) == -1)){
	   perror("Failed to initialize the signal mask");
	   return 1;
	}
    if (sigprocmask(SIG_BLOCK, &sigset, NULL) == -1){
        printf("Could not block signal");
        exit(0);
    }
	printf("Blocking all signals now...\n");
	sleep(10);
    if (sigprocmask(SIG_UNBLOCK, &sigset, NULL) == -1){
        printf("Could not unblock signal");
        exit(0);
    }
	printf("Unblocking\n");
	sleep(10);
	return 0;
}


void sighandler(int signum){
	printf("This is my custom handler.\n");
	signal(signum, SIG_DFL);
}
