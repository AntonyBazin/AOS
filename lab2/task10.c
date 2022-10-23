#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

/*
семейство execl, execlp, execle - с переменным числом параметров
execv, execvp, execve - с передачей указателя на массив
NB! пример программы, у которой работа зависит от ее имени?
*/

int main(int argc, char* argv[], char** envp){
        int rc;
        if (argc<3){
            fprintf(stderr, "Usage: %s filename command args ...\n", argv[0]);
            exit(1);
        }
        if (fork()){
            for (char **env = envp; *env != 0; env++){
                char *thisEnv = *env;
                printf("%s\n", thisEnv); 
            }
            printf("\n\n\n");
            wait(&rc);
            fprintf(stderr, "rc=%d\n", rc);
            exit(0);
        }
        else{
            execvp(argv[1], argv+1); // 1st parameter - program name
            perror(argv[2]);
            exit(1);
        }
}