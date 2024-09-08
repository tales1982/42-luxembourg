/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:50:21 by tales             #+#    #+#             */
/*   Updated: 2024/09/08 13:53:32 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Função para executar um comando

int	main(void)
{
	char	*input;
	int		i;

	char *argv[100]; // Supondo no máximo 100 argumentos
	signal(SIGINT, handle_sigint); // Trata o CTRL+C
	print_ascii();
	while (1)
	{
		// Lê a linha de comando do usuário
		input = readline("minishell> ");
		if (!input)
			break ; // Se o usuário pressionar CTRL+D, encerra o shell
		if (*input)
			add_history(input); // Adiciona à história de comandos/
		i = 0;
		argv[i] = strtok(input, " ");
		while (argv[i] != NULL && i < 99)
			argv[++i] = strtok(NULL, " ");
		// Verifica se há um comando para executar
		if (argv[0])
			exec(argv, i, environ);// Usa a variável global `environ` para passar o ambiente
		free(input); // Libera a memória alocada por readline
	}
	return (0);
}
