/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:50:21 by tales             #+#    #+#             */
/*   Updated: 2024/09/08 12:52:23 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_ascii(void)
{
   printf("\033[1;32m");  // Cor verde
    printf("*************************************************************************\n");
    printf("*  __  __  _____  _   _  _____   _____  _    _  ______  _       _     	*\n");
    printf("* |  \\/  ||_   _|| \\ | ||_   _| / ____|| |  | ||  ____|| |     | |	*\n");
    printf("* | \\  / |  | |  |  \\| |  | |  | (___  | |__| || |__   | |     | |   	*\n");
    printf("* | |\\/| |  | |  | . ` |  | |   \\___ \\ |  __  ||  __|  | |     | |  	*\n");
    printf("* | |  | | _| |_ | |\\  | _| |_  ____) || |  | || |____ | |____ | |____	*\n");
    printf("* |_|  |_||_____||_| \\_||_____||_____/ |_|  |_||______||______||______|	*\n");
    printf("*************************************************************************	\n");
    printf("\033[1;34m");  // Cor azul
    printf("*                        by Filipe, Tales                             * *\n");
    printf("*************************************************************************\n");
    printf("\033[0m");  // Resetar cor
}


// Função para escrever mensagem de erro
int err(char *str)
{
    while (*str)
        write(2, str++, 1);
    return 1;
}

// Função para mudar o diretório atual (comando 'cd')
int cd(char **argv, int i)
{
    if (i != 2)
        return err("error: cd: bad arguments\n"), 1;
    if (chdir(argv[1]) == -1)
        return err("error: cd: cannot change directory to "), err(argv[1]), err("\n"), 1;
    return 0;
}

// Função para buscar o comando na variável de ambiente PATH
char *search_path(char *cmd, char **envp)
{
    char *env_path = NULL;
    char *token = NULL;
    char *full_path = malloc(1024);
    int i = 0;

    if (!full_path)  // Verifica se o malloc falhou
        return NULL;

    // Busca a variável PATH no ambiente
    while (envp[i]) {
        if (strncmp(envp[i], "PATH=", 5) == 0) {
            env_path = strdup(envp[i] + 5);  // Faz uma cópia da variável PATH
            if (!env_path) {  // Verifica se o strdup falhou
                free(full_path);
                return NULL;
            }
            break;
        }
        i++;
    }

    if (!env_path) {
        free(full_path);
        return NULL;
    }

    // Divide o PATH em diretórios, separados por ':'
    token = strtok(env_path, ":");
    while (token) {
        sprintf(full_path, "%s/%s", token, cmd);
        if (access(full_path, X_OK) == 0) {
            free(env_path);  // Libera a memória alocada
            return full_path;
        }
        token = strtok(NULL, ":");
    }

    free(full_path);
    free(env_path);  // Libera a cópia da variável PATH
    return NULL;
}


// Função para configurar o pipe
void set_pipe(int has_pipe, int *fd, int end)
{
    if (has_pipe && (dup2(fd[end], end) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
        err("error: fatal\n"), exit(1);
}

// Função para executar um comando
int exec(char **argv, int i, char **envp)
{
    int has_pipe, fd[2], pid, status;
    char *cmd_path;

    has_pipe = argv[i] && !strcmp(argv[i], "|");

    if (!has_pipe && !strcmp(*argv, "cd"))
        return cd(argv, i);

    if (has_pipe && pipe(fd) == -1)
        err("error: fatal\n"), exit(1);

    if ((pid = fork()) == -1)
        err("error: fatal\n"), exit(1);
    if (!pid)
    {
        argv[i] = 0;
        set_pipe(has_pipe, fd, 1);

        // Busca o caminho do comando no PATH
        cmd_path = search_path(argv[0], envp);
        if (!cmd_path) {
            err("error: cannot execute "), err(*argv), err("\n"), exit(1);
        }

        // Executa o comando encontrado
        execve(cmd_path, argv, envp);
        err("error: cannot execute "), err(*argv), err("\n"), exit(1);
    }

    waitpid(pid, &status, 0);
    set_pipe(has_pipe, fd, 0);
    return WIFEXITED(status) && WEXITSTATUS(status);
}

void handle_sigint(int sig)
{
    (void)sig;
    printf("\nminishell> ");
    fflush(stdout);
}

int main(void)
{
    char *input;
    char *argv[100];  // Supondo no máximo 100 argumentos
    int i;

    signal(SIGINT, handle_sigint);  // Trata o CTRL+C
	print_ascii();
    while (1)
    {
        // Lê a linha de comando do usuário
        
        input = readline("minishell> ");
        if (!input)
            break;  // Se o usuário pressionar CTRL+D, encerra o shell

        if (*input)
            add_history(input);  // Adiciona à história de comandos

        // Divide a linha de comando em argumentos
        i = 0;
        argv[i] = strtok(input, " ");
        while (argv[i] != NULL && i < 99)
            argv[++i] = strtok(NULL, " ");

        // Verifica se há um comando para executar
        if (argv[0])
            exec(argv, i, environ);  // Usa a variável global `environ` para passar o ambiente

        free(input);  // Libera a memória alocada por readline
    }
    return 0;
}

// compilacao provisoria 
// cc minishell_v2.c -lreadline -o minishell

