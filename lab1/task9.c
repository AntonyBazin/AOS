#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>


int cpy();

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
    } else {
        printf("Usage: %s [file1 file2]\n", argv[0]);
        exit(1);
    }

    dup2(fd1, STDIN_FILENO);
    dup2(fd2, STDOUT_FILENO);

    if(cpy_flag = cpy()){
    	perror("Copying error!");
    }

    close(fd1);
    close(fd2);
    exit(0);
}



int cpy(){
    char buffer[1024] = {0};
    long bytes_count = 1024;
    while((bytes_count = read(STDIN_FILENO, buffer, 1024)) > 0){
        if(write(STDOUT_FILENO, buffer, bytes_count) != bytes_count){
            return(1);
        }
    }
    return 0;
}


