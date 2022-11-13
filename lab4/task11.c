#define _GNU_SOURCE
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>


int main() {
    pid_t pid;
    int r;

    struct flock locker;
    locker.l_type = F_WRLCK;
    locker.l_whence = SEEK_SET;
    locker.l_start = 0;
    locker.l_len = 0;

    if((pid=fork())) {
        char type[7] = "Parent:";
        while(1) {
            char buf[10] = {0};
            while(fcntl(STDOUT_FILENO, F_SETLK, &locker) == -1);
            r = read(STDIN_FILENO, buf, 10);
            write(STDOUT_FILENO, strcat(type, buf), sizeof(type) + r);
            locker.l_type = F_UNLCK;
            fcntl(STDOUT_FILENO, F_SETLK, &locker);
        }
    } else {
        char type[7] = "Child:";
        while(1) {
            char buf[10] = {0};
            while(fcntl(STDOUT_FILENO, F_SETLK, &locker) == -1);
            r = read(STDIN_FILENO, buf, 10);
            write(STDOUT_FILENO, strcat(type, buf), sizeof(type) + r);
            locker.l_type = F_UNLCK;
            fcntl(STDOUT_FILENO, F_SETLK, &locker);
        }
    }
}