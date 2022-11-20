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
	int fifofile1, fifofile2;
	ssize_t message_len;
	const char *fname = "temp";
	char buf[256] = {0};
	(void)argv; // suppressing the warning of unused function argument
	if (argc == 1)
		if (mknod(fname, 0755, S_IFIFO) == -1) {
			perror("mknod");
			exit(1);
		}

 	if ((fifofile2 = open(fname, O_RDONLY | O_NDELAY)) == -1) {
		perror("open fifofile 2");
		exit(1);
	}

	if ((fifofile1 = open(fname, O_WRONLY | O_NDELAY)) == -1) {
		perror("open fifofile 1");
		exit(1);
	}

	
	if((pid=fork())){
		close(fifofile2);
		while ((message_len = read(STDIN_FILENO, buf, 255)) != 0){
			sleep(2);
			if(message_len == -1){
				printf("Parent - read error\n");
			} else {
				buf[message_len] = 0;
				printf("Parent - sending to file: %s\n", buf);
				if ((message_len = write(fifofile1, buf, 255)) == -1){
					printf("Parent - write() error!\n");
					continue;
				}
			}
		}
		close(fifofile1);
		wait(NULL);
	} else{
		close(fifofile1);
		while(1) {
			sleep(2);
			if ((message_len = read(fifofile2, buf, 255)) == -1){
				printf("Child - read error\n");
				continue;
			} else {
				buf[message_len] = 0;
				printf("Child - file contents: %s\n", buf);
			}
		}
		close(fifofile2);
        exit(0);
	}

	return 0;
}