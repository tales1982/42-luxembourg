/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 13:28:07 by tales             #+#    #+#             */
/*   Updated: 2024/09/08 13:52:31 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

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