#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if (argc != 2) {
        printf("Usage: %s filename\n", argv[0]);
        exit(1);
    }
    char buf[2] = {0};
    int fd = open(argv[1], O_RDONLY);
    off_t fsize = lseek(fd, 0, SEEK_END);
    while(lseek(fd, fsize--, SEEK_SET) >= 0){
        read(fd, &buf[0], 1);
        printf("%s", buf);
    }
    exit(1);
}
