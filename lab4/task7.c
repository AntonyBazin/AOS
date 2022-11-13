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


extern int errno;

int main(int argc, char *argv[]){
	int fd1, fd2;

	if (argc != 2){
		printf("Usage: %s fname\n", argv[0]);
		exit(1);
	}

	const char *msg = "A message!";


	if (fork()) {

		if (fd1 = open(argv[1], O_RDWR | O_CREAT, 0755) == -1) {
			perror("open fifofile!\n");
			exit(1);
		}

        printf("I am father after fork. My PID is %d PPID is %d\n",
            getpid(), getppid());
        char parentb[100] = {0};
        for(int i = 0; i < 10; ++i){
        	printf("Write: %s\n", msg);
            write(fd1, msg, strlen(msg));
        }
        wait(NULL);
        close(fd1);
        close(fd2);
        } else {
        	if (fd2 = open(argv[1], O_RDWR | O_CREAT, 0755) == -1) {
				perror("open shared file!\n");
				exit(1);
			}
            printf("I am son after fork. My PID is %d PPID is %d\n",
                        getpid(), getppid());
            char childb[100] = {0};
            for(int i = 0; i < 10; ++i) {
                read(fd2, childb, 0);
          		printf("Read: %s\n", childb);
            }
        	exit(2);
        }
	return 0;
}