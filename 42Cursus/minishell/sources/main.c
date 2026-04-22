/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-fif <luis-fif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 15:08:24 by anolivei          #+#    #+#             */
/*   Updated: 2024/11/04 16:30:58 by luis-fif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_tiny	tiny;

	init(&tiny);
	while (1)
	{
		init_1(&tiny);
		tiny.line_read = readline("<minishell>");
		if (tiny.line_read)
		{
			add_history(tiny.line_read);
			if (ft_strlen(tiny.line_read) != 0)
			{
				split_cmd(&tiny, tiny.line_read, 0);
				if (tiny.split.n_comand > 0 && tiny.commands[0][0] != '|')
					run_commands(&tiny);
				if (tiny.commands[0] && tiny.commands[0][0] == '|')
					printf(ERROR_PIPE);
				free_char_array2(tiny.commands);
			}
			free(tiny.line_read);
		}
		else
			run_signals(3);
	}
}

void	init_1(t_tiny *tiny)
{
	tiny->out_fd = STDOUT_FILENO;
	tiny->in_fd = STDIN_FILENO;
	run_signals(1);
}

void	init(t_tiny *tiny)
{
	int	i;

	i = 0;
	tiny->last_exit_cmd = 0;
	tiny->is_builtin = false;
	tiny->has_flag = false;
	tiny->is_append = 0;
	tiny->last_redir = 0;
	tiny->out_fd = STDOUT_FILENO;
	tiny->in_fd = STDIN_FILENO;
	tiny->num_tokens = 0;
	tiny->c = 0;
	tiny->quote = '\0';
	tiny->line = NULL;
	tiny->line_read = NULL;
	tiny->name_file = NULL;
	tiny->error_name_file = NULL;
	tiny->home = NULL;
	tiny->token_aux = NULL;
	while (i < 50)
	{
		tiny->commands[i] = NULL;
		i++;
	}
	init_environment(tiny);
}

void	init_environment(t_tiny *tiny)
{
	tiny->tokens = NULL;
	tiny->path = NULL;
	print_header();
	create_env(tiny, __environ);
	init_path(tiny);
	tiny->home = ft_strdup(find_env(tiny, "HOME"));
}
