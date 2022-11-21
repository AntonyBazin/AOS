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

	struct flock wrlocker, unlocker, rlocker;
	wrlocker.l_type = F_WRLCK;
	wrlocker.l_whence = SEEK_SET;
	wrlocker.l_start = 0;
	wrlocker.l_len = 0;
	unlocker.l_type = F_UNLCK;
	unlocker.l_whence = SEEK_SET;
	unlocker.l_start = 0;
	unlocker.l_len = 0;
	rlocker.l_type = F_RDLCK;
	rlocker.l_whence = SEEK_SET;
	rlocker.l_start = 0;
	rlocker.l_len = 0;

	if (argc != 2){
		printf("Usage: %s fname\n", argv[0]);
		exit(1);
	}

	char msg[2];


	if (fork()) {

		if (((fd1 = open(argv[1], O_WRONLY | O_CREAT, 0755)) == -1)) {
			perror("opening file failed\n");
			exit(1);
		}

        printf("I am father after fork. My PID is %d FD1 is %d\n",
            getpid(), fd1);
        char parentb[100] = {0};
        for(int i = 0; i < 10; ++i) {
        	if (fcntl(fd1, F_SETLKW, &wrlocker) == -1) {
				printf("fcntl - cannot set wrlock\n");
				continue;
			}
			sprintf(msg, "%d", i);
        	printf("Write: %s\n", msg);
        	//lseek(fd1, 0, SEEK_END);
            write(fd1, msg, strlen(msg));
            if (fcntl(fd1, F_SETLK, &unlocker) == -1) {
				printf("fcntl - cannot unset wrlock\n");
				continue;
			}
        }
        wait(NULL);
        close(fd1);
        close(fd2);
        } else {
        	if (((fd2 = open(argv[1], O_RDONLY)) == -1)) {
				perror("Son cannot open shared file\n");
				exit(1);
			}
            printf("I am son after fork. My PID is %d FD2 is %d\n",
            	getpid(), fd2);
            char childb[1] = {0};
            for(int i = 0; i < 10; ++i) {
            	//lseek(fd2, 0, SEEK_SET);
                read(fd2, childb, 1);
          		printf("Read: %s\n", childb);
            }
        	exit(2);
        }
	return 0;
}