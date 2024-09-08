/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 13:40:54 by tales             #+#    #+#             */
/*   Updated: 2024/09/08 13:46:44 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// Função para liberar array de strings (como argv ou envp)
void free_string_array(char **array)
{
    int i = 0;
    if (!array)
        return;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}

// Função para liberar todas as memórias alocadas dinamicamente
void free_resources(char *input, char **argv, char *cmd_path)
{
    if (input)
        free(input);  // Libera a entrada de linha do readline

    if (argv)
        free_string_array(argv);  // Libera o array de argumentos

    if (cmd_path)
        free(cmd_path);  // Libera o caminho completo do comando
}