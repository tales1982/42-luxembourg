#ifndef MICROSHEL_H
#define MICROSHEL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

/* Macro para o prompt do shell */
#define PROMPT "microshel$ "
/* Tamanho do buffer para leitura de comandos */
#define BUFFER_SIZE 1024

/* Estrutura para armazenar informações sobre um comando */
typedef struct s_command
{
    char **args;   // Array de argumentos
    char *path;    // Caminho para o executável
} t_command;

/* Funções para leitura e análise do input */
char    *read_input(void);
char    **parse_input(char *input);

/* Funções para execução de comandos */
int     execute_command(t_command *cmd);
int     launch_process(t_command *cmd);

/* Função para liberar a memória alocada para um comando */
void    free_command(t_command *cmd);

#endif // MICROSHEL_H
