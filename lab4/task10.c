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

    if((pid=fork())) {
        char type[7] = "Parent:";
        while(1) {
            char buf[10] = {0};
            r = read(STDIN_FILENO, buf, 10);
            write(STDOUT_FILENO, strcat(type, buf), sizeof(type) + r);
        }
    } else {
        char type[7] = "Child:";
        while(1) {
            char buf[10] = {0};
            r = read(STDIN_FILENO, buf, 10);
            write(STDOUT_FILENO, strcat(type, buf), sizeof(type) + r);
        }
    }
}