/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-fif <luis-fif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 12:18:46 by anolivei          #+#    #+#             */
/*   Updated: 2024/11/04 16:31:01 by luis-fif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_commands(t_tiny *tiny)
{
	int	j;
	int	fd[2];

	j = 0;
	tiny->c = 0;
	tiny->last_redir = 0;
	while (j < tiny->split.qtt_pipe)
	{
		if (pipe(fd) < 0)
		{
			printf("Pipe error\n");
			tiny->last_exit_cmd = 127;
		}
		tiny->out_fd = fd[1];
		run_commands_aux(tiny);
		close(tiny->out_fd);
		if (tiny->in_fd != 0)
			close(tiny->in_fd);
		tiny->in_fd = fd[0];
		j++;
	}
	run_commands_aux(tiny);
}

void	run_commands_aux(t_tiny *tiny)
{
	action(tiny);
	if (tiny->commands[0][0] != '>')
	{
		tokenizer(tiny);
		if (tiny->tokens[0])
			is_builtin(tiny->tokens[0], tiny);
		if (tiny->in_fd != -1)
			exec_process(tiny, tiny->in_fd, tiny->out_fd);
		free_char_array(tiny->tokens);
		free(tiny->token.to_print);
		free(tiny->token.to_exec);
	}
	if (tiny->name_file)
		unlink(tiny->name_file);
}

void	action(t_tiny *tiny)
{
	tiny->line = ft_strdup(tiny->commands[tiny->c]);
	if (tiny->split.n_comand > 1)
		tiny->c++;
	tiny->error_name_file = NULL;
	while (tiny->commands[tiny->c] && tiny->commands[tiny->c][0] != '|')
	{
		redirect_out(tiny, tiny->c);
		redirect_in(tiny, tiny->c, NULL);
		tiny->c++;
	}
	if (tiny->error_name_file != NULL)
	{
		tiny->last_exit_cmd = 1;
		printf("minishell: %s: %s", tiny->error_name_file, ERROR_DIR);
		free(tiny->error_name_file);
	}
}

void	exec_process(t_tiny *tiny, int in, int out)
{
	pid_t	pid;

	if (tiny->is_builtin && tiny->tokens[0])
		run_builtin(tiny);
	else
	{
		pid = fork();
		run_signals(2);
		if (pid < 0)
		{
			printf("Fork error\n");
			tiny->last_exit_cmd = 127;
		}
		else if (pid == 0)
		{
			file_descriptor_handler(in, out);
			tiny->last_exit_cmd = 127;
			ft_execve_pipe(tiny, 0, "");
			exit(tiny->last_exit_cmd);
		}
		else
			waitpid(pid, &tiny->last_exit_cmd, WUNTRACED);
		if (WIFEXITED(tiny->last_exit_cmd))
			tiny->last_exit_cmd = WEXITSTATUS(tiny->last_exit_cmd);
	}
}

void	ft_execve_pipe(t_tiny *tiny, int i, char *command)
{
	if (tiny->tokens[0])
	{
		tiny->last_exit_cmd = execve(tiny->tokens[0], &tiny->tokens[0],
				tiny->env.env);
		while (tiny->path && tiny->path[i] != NULL)
		{
			command = ft_strdup(tiny->path[i]);
			if (tiny->tokens[0][0] == '|' && tiny->tokens[1])
			{
				if (!tiny->tokens[0][1])
					spaces_in_pipe(tiny, 2, command);
				else
				{
					tiny->tokens[0] = &tiny->tokens[0][1];
					spaces_in_pipe(tiny, 1, command);
				}
			}
			else
				spaces_in_pipe(tiny, 1, command);
			i++;
		}
		execve_error(tiny);
	}
}
