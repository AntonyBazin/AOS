#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>
#include <unistd.h>


struct message{
    long type;
    char text[1];
};


int main(int argc, char* argv[], char* envp[]){ //use ipcs -a here
    key_t key;
    int msgid, k;
    struct message *m2;
    struct msqid_ds msqid_buffer;

    if ((key=ftok(argv[0], 'A')) == -1){
        perror(argv[0]);
        exit(1);
    }
    if ((msgid = msgget(key, IPC_CREAT | 0600)) == -1){
        perror("msgget");
        exit(1);
    }
    m2 = malloc(14);
    m2->type = 0;
    strcpy(m2->text, "aaaaaaaaa");
    if ((k = msgrcv(msgid, m2, 5, 0, IPC_NOWAIT)) == -1){
        perror("msgrcv");
        free(m2);
        msgctl(msgid, IPC_RMID, 0);
        exit(1);
    }
    printf("k (bytes copied): %d\n", k);
    printf("m2->type = %ld, m2->text = '%s'\n", m2->type, m2->text);
    free(m2);
    if (msgctl(msgid, IPC_STAT, &msqid_buffer) == -1) {
        perror("msgctl");
        exit(1);
    }
    exit(0);
}