/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-fif <luis-fif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 23:07:24 by anolivei          #+#    #+#             */
/*   Updated: 2024/11/04 16:30:53 by luis-fif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_path(t_tiny *tiny)
{
	char	*path_aux;
	int		i;

	path_aux = ft_strdup(find_env(tiny, "PATH"));
	if (!path_aux)
		return (0);
	tiny->path = ft_split(path_aux, ':');
	i = 0;
	while (tiny->path && tiny->path[i])
	{
		tiny->path[i] = ft_strjoin(tiny->path[i], "/");
		i++;
	}
	free(path_aux);
	return (1);
}
