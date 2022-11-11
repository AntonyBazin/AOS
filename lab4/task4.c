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
	ssize_t message_len;
	char buf[256] = {0};

	if (argc < 3){
        fprintf(stderr, "Usage: %s filename command args (%s ./bash_script.sh arg1 arg2 ...)\n", argv[0], argv[0]);
        exit(1);
    }

	if (pipe2(pipe_1, O_NONBLOCK) == -1){
		perror("pipe");
		exit(1);
	}

	if((pid=fork())){
		close(pipe_1[1]);
		sleep(1);

		while ((message_len = read(pipe_1[0], buf, 255)) != 0) {
			if (message_len == -1)
				printf("Parent - read error\n");
			else {
				printf("Parent - message from child: \"%s\"\n\n", buf);
				memset(buf, 0, 255);
				sleep(1);
			}
		}
		close(pipe_1[0]);
		wait(NULL);
	} else{
		close(pipe_1[0]);
		dup2(pipe_1[1], STDOUT_FILENO);
		execvp(argv[1], argv+1);
		close(pipe_1[1]);
        exit(0);
	}

	return 0;
}