#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char* argv[]){
        int rc;
        if (argc<3){
            fprintf(stderr, "Usage: %s command args ...\n", argv[0]);
            exit(1);
        }
        if (fork()){
            wait(&rc);
            fprintf(stderr, "rc=%d\n", rc);
            exit(0);
        }
        else{
            execvp(argv[1], argv+1);
            perror(argv[2]);
            exit(1);
        }
}