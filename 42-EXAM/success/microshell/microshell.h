#ifndef MICRO_SHELL_H
#define MICRO_SHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

#define STDIN   0
#define STDOUT  1
#define STDERR  2

#define TYPE_END   3
#define TYPE_PIPE  4
#define TYPE_BREAK 5

typedef struct s_base
{
    char **argv;
    int size;
    int type;
    int fd[2];
    struct s_base *prev;
    struct s_base *next;
} t_base;

// Utilitários
int     ft_strlen(char *str);
char    *ft_strdup(char *str);

// Tratamento de erros
void    exit_fatal(void);
void    exit_execve(char *str);
int     exit_cd_1(void);
int     exit_cd_2(char *str);

// Parsing dos argumentos
void    ft_lstadd_back(t_base **ptr, t_base *new);
int     size_argv(char **argv);
int     check_end(char *av);
int     parser_argv(t_base **ptr, char **av);

// Execução dos comandos
void    exec_cmd(t_base *temp, char **env);
void    exec_cmds(t_base *ptr, char **env);

// Liberação de memória
void    free_all(t_base *ptr);

#endif
