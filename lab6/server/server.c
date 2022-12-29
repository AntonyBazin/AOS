#include "server.h"

int get_randint(int n) {
    int fd;
    int randint;
    if ((fd=open("/dev/urandom", O_RDONLY | O_NOCTTY))==-1){
        write_log("Cannot open /dev/urandom\n");
        close(fd);
        return 1;
    }
    if (read(fd, &randint, sizeof(int)) == -1) {
        write_log("Cannot read from /dev/urandom\n");
        close(fd);
        return 1;
    }
    if (close(fd) == -1) {
        write_log("Cannot close /dev/urandom\n");
        return 1;
    }
    return randint % n;
}

void write_log(const char* what){
    struct flock wr_locker, unlocker;
    wr_locker.l_type = F_WRLCK;
    wr_locker.l_whence = SEEK_SET;
    wr_locker.l_start = 0;
    wr_locker.l_len = 0;
    unlocker.l_type = F_UNLCK;
    unlocker.l_whence = SEEK_SET;
    unlocker.l_start = 0;
    unlocker.l_len = 0;


    if (fcntl(log_fd, F_SETLKW, &wr_locker) == -1) {
        syslog(LOG_INFO, "fcntl - cannot SET wr_lock for log file: %m\n"); // %m == strerror(errno) (from man)
    }

    write(log_fd, what, strlen(what));
    write(log_fd, "\n", 1);

    if (fcntl(log_fd, F_SETLKW, &unlocker) == -1) {
        syslog(LOG_INFO, "fcntl - cannot UNSET wr_lock for log file: %m\n");
    }
}

void master(){
    struct sockaddr_in client_addr, server_addr;
    unsigned int client_len;
    int sock;
    int connection;
    sigset_t sigset;

    setsid();
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGHUP);
    sigprocmask(SIG_BLOCK, &sigset, NULL);

    openlog("math_game", LOG_PID, LOG_USER);
    syslog(LOG_INFO, "Master process started\n");

    key_t ipc_key = ftok(server_name, IPC_PRIVATE);
    write_log("IPC key received\n");

    if ((semaphore_id = semget(ipc_key, 1, IPC_CREAT | 0666)) == -1) {
        write_log("semget: unable to get semaphore ID ");
        write_log(strerror(errno));
    }
    write_log("Semaphore ID acquired\n");

    if ((shared_mem_id = shmget(ipc_key, sizeof(game_t), IPC_CREAT | 0666)) == -1) {
        write_log("shmget: unable to get shared memory ID ");
        write_log(strerror(errno));
    }
    write_log("Shared memory ID acquired\n");

    if ((game = shmat(shared_mem_id, NULL, SHM_RND)) == (void *)-1) {
        write_log("shmat: unable to attach shared memory ");
        write_log(strerror(errno));
    }
    write_log("Attached shared memory\n");

    game->sem = semaphore_id;


    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        write_log("socket: unable to create socket ");
        write_log(strerror(errno));
        exit(EXIT_FAILURE);
    }
    write_log("Created socket\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port);

    if (bind(sock, (const struct sockaddr*)&server_addr, sizeof(server_addr))) {
        write_log("bind: socket bind failed ");
        write_log(strerror(errno));
        exit(EXIT_FAILURE);
    }
    write_log("Socket bound\n");

    if (listen(sock, 3)) {
        write_log("listen: failed to listen to socket ");
        write_log(strerror(errno));
        exit(EXIT_FAILURE);
    }
    write_log("Now listening to socket\n");

    while(1){
        if ((connection = accept(sock, (struct sockaddr*)&client_addr, &client_len)) == -1) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        sigemptyset(&sigset);
        sigaddset(&sigset, SIGHUP);
        sigprocmask(SIG_BLOCK, &sigset, NULL);

        char accepted_message[255];
        write_log("Accepted request from ");
        write_log(inet_ntoa(client_addr.sin_addr));
        write_log("\n");

        handler(connection);
        sigemptyset(&sigset);
        sigaddset(&sigset, SIGHUP);
        sigprocmask(SIG_UNBLOCK, &sigset, NULL);
    }

}


void handler(int conn){
    const char *cmd = "start";
    char *response;
    char user_cmd[strlen(cmd) + 1];
    memset(user_cmd, 0, strlen(cmd) + 1);
    if (read(conn, user_cmd, strlen(cmd)) == -1) {
        write_log("read: unable to read from socket ");
        write_log(strerror(errno));
        return;
    }
    write_log("Reading from socket: success\n");

    if (strcmp(user_cmd, cmd) != 0) {
        char message[255];
        strcpy(message, "Unknown user_cmd: ");
        strcat(message, user_cmd);
        write_log(message);

        response = "Список доступных команд: 1. generate";
        u_short status = strlen(response) + 1;
        write(conn, &status, sizeof(u_short));
        write(conn, response, strlen(response) + 1);
        return;
    }
}