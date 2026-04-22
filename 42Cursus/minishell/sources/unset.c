/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-fif <luis-fif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 23:25:01 by anolivei          #+#    #+#             */
/*   Updated: 2024/11/04 16:31:31 by luis-fif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_tiny *tiny)
{
	int	i;

	i = 1;
	while (tiny->tokens[i])
	{
		if (find_env(tiny, tiny->tokens[i]))
		{
			rm_env(tiny);
			if (!ft_strncmp(tiny->tokens[i], "PATH", 4))
			{
				free_char_array(tiny->path);
				tiny->path = NULL;
			}
		}
		i++;
	}
	tiny->last_exit_cmd = 0;
}

void	rm_env(t_tiny *tiny)
{
	int	i;
	int	j;

	tiny->env.len--;
	alloc_env_aux(tiny);
	i = 0;
	j = 0;
	while (i < tiny->env.len + 1)
	{
		if (i != tiny->env.index)
		{
			tiny->env_aux.key[j] = ft_strdup(tiny->env.key[i]);
			tiny->env_aux.content[j] = ft_strdup(tiny->env.content[i]);
			j++;
		}
		i++;
	}
	tiny->env_aux.key[j] = NULL;
	tiny->env_aux.content[j] = NULL;
	free_char_array(tiny->env.key);
	free_char_array(tiny->env.content);
	tiny->env.key = tiny->env_aux.key;
	tiny->env.content = tiny->env_aux.content;
}

void	alloc_env_aux(t_tiny *tiny)
{
	tiny->env_aux.key = malloc(sizeof(char *) * (tiny->env.len + 1));
	if (!tiny->env_aux.key)
		exit(EXIT_FAILURE);
	tiny->env_aux.content = malloc(sizeof(char *) * (tiny->env.len + 1));
	if (!tiny->env_aux.content)
		exit(EXIT_FAILURE);
}
