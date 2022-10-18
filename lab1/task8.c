#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>


int cpy(int, int);

int main(int argc, char *argv[]){
    int fd1 = STDIN_FILENO;
    int fd2 = STDOUT_FILENO;
    char* file1, *file2;
    int cpy_flag = 0;

    if (argc == 3) {
        file1 = argv[1];
        file2 = argv[2];
        if(((fd1 = open(file1, O_RDONLY)) == -1) || ((fd2=open(file2, O_CREAT|O_WRONLY|O_TRUNC, 0755)) == -1)){
			perror("Problem reading input");
			exit(1);
        }
    } else if(argc == 2){
        printf("Usage: %s [file1 file2]\n", argv[0]);
        exit(1);
    }

    if(cpy_flag = cpy(fd1, fd2)){
    	perror("Copying error!");
    }

    close(fd1);
    close(fd2);
    exit(0);
}



int cpy(int fd1, int fd2){
    char buffer[1024] = {0};
    long bytes_count = 1024;
    while((bytes_count = read(fd1, buffer, 1024)) > 0){
        printf("Read %ld bytes\n", bytes_count);
        if(write(fd2, buffer, bytes_count) != bytes_count){
            return(1);
        }
    }
    printf("Successfully wrote all the contents!\n");
    return 0;
}


