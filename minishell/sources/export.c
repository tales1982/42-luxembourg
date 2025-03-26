/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-fif <luis-fif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 23:53:54 by anolivei          #+#    #+#             */
/*   Updated: 2024/11/04 16:30:23 by luis-fif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_tiny *tiny)
{
	int		i;
	char	**env_aux;

	i = 1;
	while (tiny->tokens[i])
	{
		env_aux = ft_split(tiny->tokens[i], '=');
		if (env_aux[1])
			verify_if_env_exists(tiny, env_aux, i);
		else if (tiny->tokens[i][ft_strlen(tiny->tokens[1]) - 1] == '=')
		{
			env_aux[1] = ft_strdup("");
			verify_if_env_exists(tiny, env_aux, i);
		}
		free(env_aux[0]);
		free(env_aux[1]);
		free(env_aux);
		env_aux = NULL;
		i++;
	}
	tiny->last_exit_cmd = 0;
}

void	verify_if_env_exists(t_tiny *tiny, char **env_aux, int i)
{
	if (find_env(tiny, env_aux[0]))
	{
		free(tiny->env.content[tiny->env.index]);
		tiny->env.content[tiny->env.index] = ft_strdup(env_aux[1]);
	}
	else
		add_env(tiny, env_aux[0], env_aux[1]);
	if (!ft_strncmp(tiny->tokens[i], "PATH", 4))
	{
		if (tiny->path)
			free_char_array(tiny->path);
		init_path(tiny);
	}
}

void	add_env(t_tiny *tiny, char *new_key, char *new_content)
{
	int	i;

	tiny->env.len++;
	alloc_env_aux(tiny);
	i = 0;
	while (i < tiny->env.len - 1)
	{
		tiny->env_aux.key[i] = ft_strdup(tiny->env.key[i]);
		tiny->env_aux.content[i] = ft_strdup(tiny->env.content[i]);
		i++;
	}
	tiny->env_aux.key[i] = ft_strdup(new_key);
	tiny->env_aux.content[i] = ft_strdup(new_content);
	i++;
	tiny->env_aux.key[i] = NULL;
	tiny->env_aux.content[i] = NULL;
	free_char_array(tiny->env.key);
	free_char_array(tiny->env.content);
	tiny->env.key = tiny->env_aux.key;
	tiny->env.content = tiny->env_aux.content;
}
