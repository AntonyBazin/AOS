#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void sighandler(int signum){
	struct sigaction act;
	act.sa_handler = SIG_DFL;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	printf("This is my custom handler.\n");
 	sigaction(SIGINT, &act, NULL);
	signal(signum, SIG_DFL);
}

int main(void){
	struct sigaction act;
	act.sa_handler = sighandler;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL); // which, act, oldact
	for (int i = 0;; ++i){
		printf("%d\n", i);
		sleep(1);
	}
	return 0;
}