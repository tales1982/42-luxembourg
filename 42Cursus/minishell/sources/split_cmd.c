/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-fif <luis-fif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 21:59:47 by anolivei          #+#    #+#             */
/*   Updated: 2024/11/04 16:31:24 by luis-fif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_cmd(t_tiny *tiny, char *in, int i)
{
	init_split_tiny(tiny);
	in = clean_spaces(in);
	while (i < (int)ft_strlen(in))
	{
		if (tiny->split.q == 0 && (in[i] == D_QUOTE || in[i] == QUOTE))
			tiny->split.q = in[i];
		else
		{
			if (tiny->split.q == in[i])
				tiny->split.q = 0;
			else
				i = count_pipe(tiny, in, i);
		}
		tiny->split.len++;
		i++;
	}
	if (ft_strlen(in) > 0)
	{
		tiny->commands[tiny->split.n_comand] = substr_ft(in, tiny->split.ini,
				i);
		tiny->split.n_comand++;
	}
	free(in);
	tiny->commands[tiny->split.n_comand] = NULL;
}

void	init_split_tiny(t_tiny *tiny)
{
	tiny->split.n_comand = 0;
	tiny->split.ini = 0;
	tiny->split.len = 0;
	tiny->split.qtt_pipe = 0;
	tiny->split.q = 0;
	tiny->last_redir = 0;
}

char	*clean_spaces(char *in)
{
	char	*aux;

	aux = ft_strtrim(in, " ");
	in = aux;
	return (in);
}

int	count_pipe(t_tiny *tiny, char *in, int i)
{
	if (in[i] == '|' || in[i] == '<' || in[i] == '>')
	{
		if (in[i] == '|' && tiny->split.q == 0)
			tiny->split.qtt_pipe++;
		if (tiny->split.q == 0 && i > 1 && tiny->split.len > 0)
		{
			tiny->commands[tiny->split.n_comand] = substr_ft(in,
					tiny->split.ini, tiny->split.len);
			tiny->split.ini = i;
			tiny->split.len = 0;
			tiny->split.n_comand++;
			if (in[i] == '>')
				tiny->last_redir = 1;
			else
				tiny->last_redir = 0;
			if (in[i] == in[i + 1])
			{
				i++;
				tiny->split.len = 1;
			}
		}
	}
	return (i);
}
