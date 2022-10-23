#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

/*
Usage: ./task7 lorem_ipsum.txt
*/


int main(int argc, char *argv[]){
	if (argc != 2) {
		printf("Usage: %s filename\n", argv[0]);
		exit(1);
	}
	int fd = open(argv[1], O_RDONLY);


    if (fork()) {
        printf("I am father after fork. My PID is %d PPID is %d, my PGID is %d\n",
            getpid(), getppid(), getpgid(getpid()));
        char parentb[200] = {0};
        int fparent = open("father_out_t8.txt", O_TRUNC | O_CREAT | O_WRONLY);
        int parread;
        while ((parread = read(fd, &parentb[0], 6))) {
#if defined PRINT
            printf("PARENT: read %d symbs:\n%s\n", parread, parentb);
#endif
            write(fparent, &parentb[0], parread);
        }
        wait(NULL);
            exit(0);
        }
        else {
            printf("I am son after fork. My PID is %d PPID is %d, my PGID is %d\n",
                        getpid(), getppid(), getpgid(getpid()));
            char childb[200] = {0};
            int fchild = open("child_out_t8.txt", O_TRUNC | O_CREAT | O_WRONLY);
            int chread;
            while ((chread = read(fd, &childb[0], 6))) {
    #if defined PRINT
                printf("CHILD: read %d symbs:\n%s\n", chread, childb);
    #endif
                write(fchild, &childb[0], chread);
            }
            exit(2);
        }
}