/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-fif <luis-fif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 22:04:28 by anolivei          #+#    #+#             */
/*   Updated: 2024/11/04 16:31:14 by luis-fif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_out(t_tiny *tiny, int j)
{
	int		flags;
	char	*file;

	flags = O_WRONLY | O_CREAT;
	j = tiny->c;
	if (tiny->commands[j] && tiny->commands[j][0] == '>')
	{
		if (tiny->commands[j] && tiny->commands[j][1] == '>')
		{
			file = ft_strtrim(&tiny->commands[j][2], " ");
			tiny->out_fd = open(file, flags | O_APPEND, 0777);
			free(file);
		}
		else
			simple_redir_out(tiny, j, flags);
		tiny->last_redir = 1;
		if (tiny->split.n_comand == 1)
			free(tiny->line);
	}
}

void	simple_redir_out(t_tiny *tiny, int j, int flags)
{
	char	*aux;
	char	*file;

	aux = ft_strtrim(&tiny->commands[j][1], " ");
	file = substr_ft(aux, 0, find_char(aux, ' '));
	tiny->out_fd = open(file, flags | O_TRUNC, 0777);
	free(aux);
	free(file);
}

int	find_char(char *string, char needle)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == needle)
			return (i);
		i++;
	}
	return (i);
}
