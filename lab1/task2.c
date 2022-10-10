#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

/*
 * 1 - ex, 2 - w, 4 - r
 * Usage: $./task2 <filename> <permissions>,
 * permissions=444
 */

extern int errno;

int main(int argc, char * argv[]){
    int l, p;
    char * ptr;
    if (argc!=3){
        fprintf(stderr, "Usage: %s file filemode\n", argv[0]);
        exit(1);
    }
    p=strtol(argv[2], &ptr, 8);
    if (strlen(argv[2])!=ptr-argv[2]){
        fprintf(stderr, "%s: incorrect filemode\n", argv[2]);
        exit(1);
    }
    l=creat(argv[1], p);
    printf("l=%d\n", l);
    exit(0);
}