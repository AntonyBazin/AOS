#include "server.h"

int main(void){
    switch(fork()) {
        case -1:
            perror("fork");
            exit(EXIT_FAILURE);
        case 0:
            master();
        default:
            exit(EXIT_SUCCESS);
    }
    exit(EXIT_SUCCESS);
}