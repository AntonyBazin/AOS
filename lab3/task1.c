#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void sighandler(int signum){
	printf("This is my custom handler.\n");
	signal(signum, SIG_DFL);
}

int main(void){
	signal(SIGINT, sighandler);
	for (int i = 0;; ++i){
		printf("%d\n", i);
		sleep(1);
	}
	return 0;
}