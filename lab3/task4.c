#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>



int main(void){
	int pid;
	int return_code;
	if((pid = fork())){
		wait(&return_code);
		printf("Child exited with %d\n", return_code);
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