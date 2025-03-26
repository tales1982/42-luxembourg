/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-fif <luis-fif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 00:04:26 by anolivei          #+#    #+#             */
/*   Updated: 2024/11/04 16:30:11 by luis-fif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_tiny *tiny)
{
	int	j;
	int	n;

	n = init_echo(tiny, 0);
	j = 0;
	if (tiny->tokens[1])
	{
		print_echo(tiny, tiny->token.to_print);
		if (!tiny->has_flag)
			ft_putstr_fd("\n", tiny->out_fd);
	}
	else
		ft_putstr_fd("\n", tiny->out_fd);
}

int	init_echo(t_tiny *tiny, int n)
{
	if (tiny->tokens[0][0] != '|')
		n = 1;
	else
		n = 2;
	return (n);
}

void	print_echo(t_tiny *tiny, char *tiny_tokens_i)
{
	if (!ft_strncmp(tiny_tokens_i, "$?", 2))
		ft_putnbr_fd(tiny->last_exit_cmd, tiny->out_fd);
	else
	{
		ft_putstr_fd(tiny_tokens_i, tiny->out_fd);
		tiny->last_exit_cmd = 0;
	}
}
