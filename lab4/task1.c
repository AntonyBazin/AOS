#define _GNU_SOURCE
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]){
	pid_t pid;
	int pipe_1[2], pipe_2[2];
	ssize_t message_len;
	char buf[256] = {0};
	if (argc < 2) {
		printf("Usage: %s [pipetype] (1 or 2)\n", argv[0]);
		exit(1);
	}
	int type = atoi(argv[1]);
	switch (type) {
	case 1:
		if (pipe(pipe_1) == -1) {
			perror("pipe 1");
			exit(1);
		}
		if (pipe(pipe_2) == -1) {
			perror("pipe 2");
			exit(1);
		}
		break;
	case 2:
		if (pipe2(pipe_1, 0) == -1) { // If  flags is 0, then pipe2() is the same as pipe().
			perror("pipe2");
			exit(1);
		}
		if (pipe2(pipe_2, 0) == -1) {
			perror("pipe2");
			exit(1);
		}
		break;
	default:
		printf("Invalid pipe type!\n");
		exit(1);
	};
	if(pid=fork()){
		close(pipe_1[1]);
		if ((message_len = read(pipe_1[0], buf, 255)) == -1)
			printf("Parent - read error\n");
		else
			printf("Parent - got message from child: \"%s\"\n", buf);
		close(pipe_1[0]);
		char string[] = "message from parent";
		close(pipe_2[0]);
		write(pipe_2[1], string, strlen(string) + 1);
		close(pipe_2[1]);
		wait(NULL);
	} else{
		char string[] = "message from child";
		close(pipe_1[0]);
		write(pipe_1[1], string, strlen(string) + 1);
		close(pipe_1[1]);
		close(pipe_2[1]);
		if ((message_len = read(pipe_2[0], buf, 255)) == -1) {
			printf("Child - read error!\n");
			exit(1);
		}
		printf("Child - got message of len %lu from parent: \"%s\"\n", 
									message_len, buf);
		close(pipe_2[0]);
	    exit(0);
	}

	return 0;
}