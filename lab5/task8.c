#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>


struct message{
    long type;
    char text[50];
};
short ENABLED = 1;



void sigint_handler(int signum){
    (void)signum;
    ENABLED = 0;
}


void server_process(){
    key_t key;
    int msgid, msgsize;
    int client_qid;
    struct message *msg;
    char msg_text[50];
    pid_t server_pid = getpid();

    signal(SIGINT, sigint_handler);

    if ((key=ftok(".", 'A')) == -1){
        perror("ftok");
        exit(1);
    }
    if ((msgid = msgget(key, IPC_CREAT | 0660)) == -1){
        perror("Server: msgget");
        exit(1);
    }
    printf("Hello from server! msgid = %d\n", msgid);

    for(int i = 0; ENABLED; ++i) {
        sleep(1);
        msg = malloc(54);
        if ((msgsize = msgrcv(msgid, msg, 50, 0, MSG_NOERROR)) == -1)
            continue;

        printf("Type = %ld, message = '%s'\n", msg->type, msg->text);
        sprintf(msg_text, "Responce %d from server to %ld", i, msg->type);
        strcpy(msg->text, msg_text);
        client_qid = msg->type;

        msg->type = server_pid;
        if (msgsnd(client_qid, msg, 50, 0) == -1){
            perror("Server: msgsnd");
            continue;
        }
        free(msg);
    }
    printf("Server: shutdown gracefully\n");
    msgctl(msgid, IPC_RMID, 0);
}


void client_process(){
    key_t key;
    int server_msgid, recv_bytes, client_msgid;
    struct message *msg;
    pid_t client_pid = getpid();
    char text[50];

    signal(SIGINT, sigint_handler);

    if ((key=ftok(".", 'A')) == -1){
        perror("ftok");
        exit(1);
    }
    if ((server_msgid = msgget(key, IPC_CREAT | 0660)) == -1){
        perror("Client: msgget key");
        exit(1);
    }
    if ((client_msgid = msgget(IPC_PRIVATE, 0660)) == -1){
        perror("Client: msgget PRIVATE");
        exit(1);
    }
    printf("Server_msgid = %d,", server_msgid);
    printf("Client_msgid = %d\n", client_msgid);

    for(int i = 0; ENABLED; ++i){
        sleep(1);
        msg = malloc(54);
        msg->type = client_msgid;
        sprintf(text, "Msg from client #%d", i);
        strcpy(msg->text, text);
        if (msgsnd(server_msgid, msg, 50, MSG_NOERROR) == -1){
            perror("Client: msgsnd");
            continue;
        }
        if ((recv_bytes = msgrcv(client_msgid, msg, 50, 0, MSG_NOERROR)) == -1){ //type = 0, read any
            perror("Client: msgrcv");
            continue;
        }
        printf("Answer type = %ld, Asnwer = '%s'\n", msg->type, msg->text);
        free(msg);
    }
    printf("Client: shutdown gracefully\n");
    msgctl(client_msgid, IPC_RMID, 0);
}



int main(int argc, char* argv[], char* envp[]){
    if (argc < 2) {
        printf("Usage: %s type (client or server)\n", argv[0]);
        exit(1);
    }
    if (!strcmp("server", argv[1]))  // call server
        server_process();
    else if (!strcmp("client", argv[1]))  //call client
        client_process();
    exit(0);
}
