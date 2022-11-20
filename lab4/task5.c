#define _GNU_SOURCE
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char* argv[]){
	pid_t pid;
	int pipe_1[2];

	if (pipe2(pipe_1, 0) == -1){
		perror("pipe");
		exit(1);
	}

	if((pid=fork())){
		close(pipe_1[1]);
		//sleep(1); // Needed, w/o it wc will not execute with "wc: 'standard input': Resource temporarily unavailable"
		dup2(pipe_1[0], STDIN_FILENO);
	    execlp("wc", "wc", "-l", NULL);
		close(pipe_1[0]);
		wait(NULL);
	} else{
		close(pipe_1[0]);
		dup2(pipe_1[1], STDOUT_FILENO);
		execlp("ls", "ls", "-l", NULL);
		close(pipe_1[1]);
       	exit(0);
	}

	return 0;
}