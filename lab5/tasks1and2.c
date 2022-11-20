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


int main(int argc, char* argv[], char* envp[]){
    key_t key;
    int msgid, k;
    struct message *m1, *m2;
    struct msqid_ds msqid_buffer;

    if ((key=ftok(argv[0], 'A')) == -1){
        perror(argv[0]);
        exit(1);
    }
    if ((msgid = msgget(key, IPC_CREAT | 0600)) == -1){
        perror("msgget");
        exit(1);
    }
    m1 = malloc(14);
    m1->type = 1;
    strcpy(m1->text, "123456789");
    if (msgsnd(msgid, m1, 9, 0) == -1){
        perror("msgsnd");
        free(m1);
        exit(1);
    }
    free(m1);
    m1 = malloc(14);
    m1->type = 1;
    strcpy(m1->text, "abcdefhij");
    if (msgsnd(msgid, m1, 9, 0) == -1){
        perror("msgsnd");
        free(m1);
        exit(1);
    }
    m2 = malloc(14);
    m2->type = 0;
    strcpy(m2->text, "aaaaaaaaa");
    if ((k = msgrcv(msgid, m2, 5, 0, MSG_NOERROR)) == -1){ //type = 0, read any
        perror("msgrcv"); //read msg of size 5, got 10 instead, use MSG_NOERROR
        free(m2);
        exit(1);
    }
    printf("k (bytes copied): %d\n", k);
    printf("m2->type = %ld, m2->text = '%s'\n", m2->type, m2->text);
    free(m2);
    if (msgctl(msgid, IPC_STAT, &msqid_buffer) == -1) {
        perror("msgctl");
        exit(1);
    }
    printf("msg_perm: uid %d, gid %d, mode %o\n", msqid_buffer.msg_perm.uid, 
                                msqid_buffer.msg_perm.gid, msqid_buffer.msg_perm.mode);
    printf("msg_stime (last snd): %ld\n", msqid_buffer.msg_stime);
    printf("msg_rtime (last rcv): %ld\n", msqid_buffer.msg_rtime);
    printf("msg_ctime (last change): %ld\n", msqid_buffer.msg_ctime);
    printf("msg_qnum (current num of msg in queue): %ld\n", msqid_buffer.msg_qnum);
    printf("msg_lspid (PID of last msgsnd): %d\n", msqid_buffer.msg_lspid);
    printf("msg_lrpid (PID of last msgrcv): %d\n", msqid_buffer.msg_lrpid);
    printf("msg_qbytes (max bytes allowed): %ld\n", msqid_buffer.msg_qbytes);
    msgctl(msgid, IPC_RMID, 0);
    exit(0);
}