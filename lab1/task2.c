#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>


extern int errno;

/*
 * 1 - ex, 2 - w, 4 - r
 * Usage: $./task2 <filename> <permissions>,
 * permissions=444
 */

extern int errno;

int main(int argc, char * argv[]){
    int l, p;
    char* ptr;
    char buff1[] = "abcdefg";
    int buffs_len = strlen(buff1);
    if (argc!=3){
        fprintf(stderr, "Usage: %s file filemode\n", argv[0]);
        exit(1);
    }
    p = strtol(argv[2], &ptr, 8);
    if (strlen(argv[2])!=ptr-argv[2]){
        fprintf(stderr, "%s: incorrect filemode\n", argv[2]);
        exit(1);
    }
    l = creat(argv[1], p);





    printf("Opening file for reading...");
    int fd;
    if ((fd=open("file.txt", O_RDONLY))==-1){
        perror(argv[1]);
        close(fd);
    }
    close(fd);

    printf("Opening file for reading and writing...");
    if ((fd=open(argv[1], O_RDWR))==-1){
        perror(argv[1]);
        printf("%d", errno);
        close(fd);
    }
    close(fd);


    exit(0);
}