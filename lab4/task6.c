#define _GNU_SOURCE
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char *argv[]){
	pid_t pid;
	int fifofile;
	ssize_t message_len;
	const char *fname = "temp";
	char buf[256] = {0};
	(void)argv; // suppressing the warning of unused function argument
	if (argc == 1)
		if (mknod(fname, S_IFIFO, 0) == -1) {
			perror("mknod");
			exit(1);
		}
	if ((fifofile = open(fname, O_RDWR | O_NONBLOCK)) == -1) {
		perror("open fifofile!\n");
		exit(1);
	}
	
	if((pid=fork())){
		while ((message_len = read(STDIN_FILENO, buf, 255)) != 0){
			if(message_len == -1){
				printf("Parent - read error\n");
			} else {
				buf[message_len] = 0;
				printf("Parent - sending to file: %s\n", buf);
				if ((message_len = write(fifofile, buf, 255)) == -1){
					printf("Parent - write() error!\n");
					continue;
				}
			}
		}
		close(fifofile);
		wait(NULL);
	} else{
		while(1) {
			if ((message_len = read(fifofile, buf, 255)) == -1){
				printf("Child - read error\n");
				continue;
			} else {
				buf[message_len] = 0;
				printf("Child - file contents: %s\n", buf);
			}
		}
		close(fifofile);
        exit(0);
	}

	return 0;
}