#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    unsigned long max_len = 0;
    char* largest_file_name;
    struct stat st_buf;

    if (argc <= 2){
        printf("Usage: %s filenames\n", argv[0]);
        exit(1);
    }
    for (int i = 1; i < argc; ++i){
        stat(argv[i], &st_buf);
        if (st_buf.st_size > max_len){
            max_len = st_buf.st_size;
            largest_file_name = &argv[i][0];
        }
    }
    printf("The largest file is \"%s\", its size is %lu bytes.\n", largest_file_name, max_len);
    exit(0);
}

