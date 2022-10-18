#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

extern int errno;

// file?.txt SHOULD NOT exist.
int try_with_errno();
int try_with_strerror();
int try_with_perror();

int main(){
    try_with_strerror();
    try_with_errno();
    try_with_perror();
    exit(0);
}

int try_with_perror(){
    if (open("file1.txt", O_RDONLY)==-1){
        perror("Perror on opening file1.txt");
        return 0;
    }
    return 0;
}

int try_with_errno(){
    int fd;
    fd = open("file2.txt", O_RDONLY);
    printf("Errno is %d and fd is %d\n\n", errno, fd);
    close(fd);
    return 0;
}

int try_with_strerror(){
    /*
     * warning: `sys_errlist' is deprecated;
     * using `strerror' or `strerror_r' instead
     */
    int fd;
    fd = open("file3.txt", O_RDONLY);
//    for(int i = 0; i < sys_nerr; ++i)
//        printf("sys_errlist[%d] = \"%s\"\n", i, sys_errlist[i]);
    printf("Error from strerror: %s\n\n", strerror(errno));
    close(fd);
    return 0;
}