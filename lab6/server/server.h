#ifndef LAB6_SERVER_H
#define LAB6_SERVER_H

#include <syslog.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
//#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>


typedef struct task{
    int op1;
    int op2;
    short opcode;
    int answer;
    int client_answer;
} task_t;

typedef struct game{
    task_t* tasks;
    unsigned int task_count;
    double accracy;
    int sem;
} game_t;


int port, log_fd, shared_mem_id, semaphore_id;
char config_name[255], log_name[255] = "", server_name[255] = "Math_server";
struct sembuf mem_lock[2] = {
        0, 0, 0,
        0, 1, 0
};
struct sembuf unlock[1] = {
        0, -1, 0
};
game_t* game;

int get_randint(int n);

void write_log(const char* what);

void sh_lock();
void sh_unlock();

void master();
void handler(int conn);

int generate_task(int first);
int update_accuracy(task_t task);


#endif //LAB6_SERVER_H
