/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-fif <luis-fif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 23:07:31 by anolivei          #+#    #+#             */
/*   Updated: 2024/11/04 16:30:15 by luis-fif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_tiny *tiny)
{
	int	i;

	i = 0;
	while (i < tiny->env.len)
	{
		ft_putstr_fd(tiny->env.key[i], tiny->out_fd);
		ft_putchar_fd('=', tiny->out_fd);
		ft_putendl_fd(tiny->env.content[i], tiny->out_fd);
		i++;
	}
	tiny->last_exit_cmd = 0;
}

void	create_env(t_tiny *tiny, char **my_env)
{
	int		i;
	char	**env_aux;

	tiny->env.env = my_env;
	len_env(tiny);
	init_tiny_env(tiny);
	i = 0;
	while (tiny->env.env[i])
	{
		env_aux = ft_split(tiny->env.env[i], '=');
		tiny->env.key[i] = ft_strdup(env_aux[0]);
		if (env_aux[1])
			tiny->env.content[i] = ft_strdup(env_aux[1]);
		else
			tiny->env.content[i] = ft_strdup("");
		free_char_array(env_aux);
		i++;
	}
	tiny->env.key[i] = NULL;
	tiny->env.content[i] = NULL;
}

void	len_env(t_tiny *tiny)
{
	int	i;

	i = 0;
	while (tiny->env.env[i])
		i++;
	tiny->env.len = i;
}

void	init_tiny_env(t_tiny *tiny)
{
	tiny->env.key = malloc(sizeof(char *) * (tiny->env.len + 1));
	if (!tiny->env.key)
		exit(EXIT_FAILURE);
	tiny->env.content = malloc(sizeof(char *) * (tiny->env.len + 1));
	if (!tiny->env.content)
		exit(EXIT_FAILURE);
}
