#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    int fd1, fd2;
    char* file1, *file2;
    int got_input = 0;
    char buffer[1024] = {0};
    long int bytes_count = 1024;

    if (argc == 3) {
        file1 = argv[1];
        file2 = argv[2];
    } else if (argc == 1) {
        got_input = 1;
        file1 = calloc(30, sizeof(*file1));
        file2 = calloc(30, sizeof(*file2));
        printf("Enter first file name: ");
        scanf("%s", file1);
        printf("Enter second file name: ");
        scanf("%s", file2);
    } else {
        printf("Usage: %s [file1 file2]\n", argv[0]);
        exit(1);
    }

    if(((fd1 = open(file1, O_RDONLY)) == -1) || ((fd2=open(file2, O_CREAT|O_WRONLY|O_TRUNC, 0755)) == -1)){
        perror("Problem reading input");
        exit(1);
    }
    //if(got_input)
    //fchmod(fd2, 0755)

     while((bytes_count = read(fd1, buffer, 1024)) > 0){
        printf("Read %ld bytes\n", bytes_count);
        if(write(fd2, buffer, bytes_count) != bytes_count){
            perror("Writing error");
            exit(1);
        }
    }
    close(fd1);
    close(fd2);
    if (got_input) {
        free(file1);
        free(file2);
    }
    printf("Successfully wrote all the contents!\n");
    exit(0);
}
