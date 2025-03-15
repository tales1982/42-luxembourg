#include "microshel.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

/* Lança o comando utilizando execvp.
   Em caso de erro, exibe a mensagem e retorna -1. */
int launch_process(t_command *cmd) {
    if (execvp(cmd->args[0], cmd->args) == -1) {
        perror("microshel");
    }
    return -1;
}

/* Cria um processo filho para executar o comando e o pai aguarda o término */
int execute_command(t_command *cmd) {
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        /* Processo filho: tenta executar o comando */
        if (launch_process(cmd) == -1)
            exit(EXIT_FAILURE);
    } else if (pid < 0) {
        /* Erro ao criar o processo */
        perror("microshel");
        return -1;
    } else {
        /* Processo pai: espera o filho terminar */
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 0;
}
