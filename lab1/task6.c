#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>


/*
 * od -c file_with_hole
 */

extern int errno;

int main(int argc, char * argv[]){
    char* ptr;
    char buff1[] = "abcdefg";
    char buff2[] = "ABCDEFG";
    int buffs_len = strlen(buff1);
    int fd;
    if (argc!=3){
        fprintf(stderr, "Usage: %s file filemode\n", argv[0]);
        exit(1);
    }
    strtol(argv[2], &ptr, 8);
    if (strlen(argv[2])!=ptr-argv[2]){
        fprintf(stderr, "%s: incorrect filemode\n", argv[2]);
        exit(1);
    }
    if((fd = creat("file_with_hole", S_IREAD|S_IWRITE)) < 0){
        perror("create file error!");
    }

    if(write(fd, buff1, buffs_len) != buffs_len){
        perror("write error!");
    }

    if(lseek(fd,5000, SEEK_CUR) == -1){
        perror("lseek error!");
    }

    if(write(fd, buff2, buffs_len) != buffs_len) {
        perror("write error!");
    }

    exit(0);
}
