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
    printf("Trying to remove existing msg queue\n");
    if (msgctl(msgid, IPC_RMID, 0) == -1) {
        perror("msgctl");
        exit(1);
    }
    printf("Trying to remove NON-existing msg queue\n");
    if (msgctl(msgid, IPC_RMID, 0) == -1) {
        perror("msgctl");
        exit(1);
    }
    exit(0);
} // are queues removed automatically?