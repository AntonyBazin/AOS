#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

// file.txt SHOULD NOT exist.
int try_with_errno();
int try_with_errlist();
int try_with_perror();

int main(){
    try_with_errlist();
    try_with_errno();
    try_with_perror();
    exit(0);
}

int try_with_perror(){
    int f;
    if ((f=open("file.txt", 'r'))==-1){
        perror("file.txt");
        exit(1);
    }
    FILE* fp;
    fp = fopen("file.txt", "r");
    if(fp == NULL){
        perror("Error from perror!");
        return(-1);
    }
    fclose(fp);
    return 0;
}

int try_with_errno(){
    int fd;
    fd = open("file.txt", 'r');
    printf("errno is %d and fd is %d\n\n\n", errno, fd);
    close(fd);
    return 0;
}

int try_with_errlist(){
    /*
     * warning: `sys_errlist' is deprecated;
     * using `strerror' or `strerror_r' instead
     */
    int fd;
    fd = open("file.txt", 'r');
    for(int i = 0; i < sys_nerr; ++i)
        printf("sys_errlist[%d] = \"%s\"\n", i, sys_errlist[i]);
    printf("\n\n");
    close(fd);
    return 0;
}