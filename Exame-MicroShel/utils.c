#include "microshel.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Lê uma linha do stdin e a retorna alocada dinamicamente */
char *read_input(void) {
    char *buffer = malloc(BUFFER_SIZE);
    if (!buffer) {
        fprintf(stderr, "Erro de alocação\n");
        exit(EXIT_FAILURE);
    }
    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
        free(buffer);
        return NULL;
    }
    return buffer;
}

/* Separa a string de input em tokens (argumentos) usando strtok
   e duplica cada token para que fiquem em memória própria. */
char **parse_input(char *input) {
    int bufsize = 64, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens) {
        fprintf(stderr, "Erro de alocação\n");
        exit(EXIT_FAILURE);
    }
    token = strtok(input, " \t\r\n");
    while (token != NULL) {
        tokens[position] = strdup(token);
        if (!tokens[position]) {
            fprintf(stderr, "Erro de alocação\n");
            exit(EXIT_FAILURE);
        }
        position++;
        if (position >= bufsize) {
            bufsize += 64;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens) {
                fprintf(stderr, "Erro de alocação\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, " \t\r\n");
    }
    tokens[position] = NULL;
    return tokens;
}

/* Libera a memória alocada para os argumentos do comando */
void free_command(t_command *cmd) {
    if (!cmd->args)
        return;
    for (int i = 0; cmd->args[i] != NULL; i++) {
        free(cmd->args[i]);
    }
    free(cmd->args);
}
