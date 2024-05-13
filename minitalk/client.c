#include "minitalk.h"

void send_char(pid_t server_pid, char c) {
    for (int i = 0; i < 8; i++) {
        if (c & (1 << i))
            kill(server_pid, SIGUSR2);
        else
            kill(server_pid, SIGUSR1);
        usleep(100);
    }
}

int main(int argc, char **argv) {
    if (argc != 3) {
        write(2, "Usage: ./client [server PID] [message]\n", 40);
        return 1;
    }

    pid_t server_pid = atoi(argv[1]);
    char *message = argv[2];

    for (int i = 0; message[i] != '\0'; i++) {
        send_char(server_pid, message[i]);
    }
    return 0;
}

