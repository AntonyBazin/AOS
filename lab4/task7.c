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

	char msg[2];


	if (fork()) {
		if (((fd1 = open(argv[1], O_WRONLY | O_CREAT, 0755)) == -1)) {
			perror("open file\n");
			exit(1);
		}
        printf("I am father after fork. My PID is %d FD1 is %d\n",
            getpid(), fd1);
        char parentb[100] = {0};

        //for(int j = 0; j < 1000; ++j); // chaotic reads and writes
        for(int i = 0; i < 100; ++i){
        	sprintf(msg, "%d", i);
        	printf("Write: %s\n", msg);
            write(fd1, msg, strlen(msg));
        }
        wait(NULL);
        close(fd1);
        close(fd2);
        } else {
        	if (((fd2 = open(argv[1], O_RDONLY)) == -1)) {
				perror("open shared file!\n");
				exit(1);
			}
            printf("I am son after fork. My PID is %d FD2 is %d\n",
            	getpid(), fd2);
            char childb[500] = {0};
            for(int i = 0; i < 100; ++i) {
                read(fd2, childb, 500);
          		printf("Read: %s\n", childb);
            }
        	exit(2);
        }
	return 0;
}