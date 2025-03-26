/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-fif <luis-fif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 00:55:08 by anolivei          #+#    #+#             */
/*   Updated: 2024/11/04 16:31:17 by luis-fif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_in(t_tiny *tiny, int j, char *aux)
{
	char	**file;

	if (tiny->commands[j][0] == '<')
	{
		file = NULL;
		if (tiny->commands[j][1] == '<')
			file = double_redir(tiny, file, j);
		else
		{
			file = ft_split(&tiny->commands[j][1], ' ');
			tiny->in_fd = open(file[0], O_RDONLY, 0777);
			if (tiny->in_fd == -1 && tiny->error_name_file == NULL)
				tiny->error_name_file = ft_strdup(file[0]);
		}
		aux = ft_strtrim(tiny->line, " ");
		if (tiny->split.n_comand == 1 || (aux[0] == '|' && ft_strlen(aux) == 1))
		{
			free(tiny->line);
			tiny->line = new_comman(1, file);
		}
		free(aux);
		tiny->last_redir = 0;
		free_char_array(file);
	}
}

char	**double_redir(t_tiny *tiny, char **file, int j)
{
	file = ft_split(&tiny->commands[j][2], ' ');
	read_until(file[0]);
	tiny->in_fd = open(file[0], O_RDONLY | O_CREAT, 0777);
	tiny->name_file = ft_strdup(file[0]);
	tiny->is_append++;
	return (file);
}

void	read_until(char *end)
{
	char	*line;
	int		flags;
	int		fd;

	flags = O_WRONLY | O_CREAT | O_TRUNC;
	line = ft_strdup("");
	fd = open(end, flags, 0777);
	while (ft_strncmp(line, end, ft_strlen(end))
		|| ft_strlen(line) != ft_strlen(end))
	{
		free(line);
		line = readline("> ");
		if (ft_strlen(line) != ft_strlen(end))
			ft_putendl_fd(line, fd);
	}
	close(fd);
	free(line);
}

char	*new_comman(int i, char **str)
{
	char	*aux;

	aux = ft_strdup("");
	while (str[i] != NULL)
	{
		if (ft_strlen(aux) > 0)
			aux = ft_strjoin(aux, " ");
		aux = ft_strjoin(aux, str[i]);
		i++;
	}
	return (aux);
}
