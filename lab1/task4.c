#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>


/*
 * 1 - ex, 2 - w, 4 - r
 * Usage: $./task2 <filename> <permissions>,
 * permissions=666
 */

extern int errno;

int main(int argc, char * argv[]){
    int cr_res, p;
    char* ptr;
    int result;
    if (argc!=3){
        fprintf(stderr, "Usage: %s file filemode\n", argv[0]);
        exit(1);
    }
    p = strtol(argv[2], &ptr, 8);
    if (strlen(argv[2])!=ptr-argv[2]){
        fprintf(stderr, "%s: incorrect filemode\n", argv[2]);
        exit(1);
    }
    cr_res = creat(argv[1], p);
    printf("Create result = %d\n", cr_res);

    printf("Opening file for writing...");
    char buf[100] = {0};
    sprintf(buf, "./2 %s rw", argv[1]);

    int fd;
    if ((fd=open(argv[1], O_RDWR))==-1){
        perror(argv[1]);
        close(fd);
    }
    result = lseek(fd, 5, SEEK_SET);
    result = read(fd, &buf[0], 4);
    printf("Read 4 symbols from pos 5");

    result = lseek(fd, 0, SEEK_END);
    result = write(fd, &buf[0], 5);

    struct stat st_buf;
    fstat(fd, &st_buf);
    result = read(fd, &buf[0], st_buf.st_size);
    printf("2: wrote 3 chars into the end of file\n%s\n", buf);
    result = close(fd);


    exit(0);
}
