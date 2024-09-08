/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:37:50 by tales             #+#    #+#             */
/*   Updated: 2024/09/08 13:42:19 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

extern char **environ;

/*
** ----- ft_error.c -----
*/
int	err(char *str);

/*
** ----- path.c -----
*/
char	*search_path(char *cmd, char **envp);

/*
** ----- exec_cmd.c -----
*/
int	exec(char **argv, int i, char **envp);
void	set_pipe(int has_pipe, int *fd, int end);

/*
** ----- signal_handler.c -----
*/
void	handle_sigint(int sig);

/*
** ----- utils.c -----
*/
int	cd(char **argv, int i);

/*
** ----- ft_print_ascii.c -----
*/
void print_ascii(void);

/*
** ----- free_resources.c -----
*/
void free_resources(char *input, char **argv, char *cmd_path);

#endif
