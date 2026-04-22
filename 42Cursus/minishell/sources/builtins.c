/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-fif <luis-fif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 22:51:31 by anolivei          #+#    #+#             */
/*   Updated: 2024/11/04 16:29:52 by luis-fif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_builtin(char *cmd, t_tiny *tiny)
{
	if ((!ft_strncmp("echo", cmd, 4) && ft_strlen(cmd) == 4)
		|| (!ft_strncmp("cd", cmd, 2) && ft_strlen(cmd) == 2)
		|| (!ft_strncmp("pwd", cmd, 3) && ft_strlen(cmd) == 3)
		|| (!ft_strncmp("export", cmd, 6) && ft_strlen(cmd) == 6)
		|| (!ft_strncmp("unset", cmd, 5) && ft_strlen(cmd) == 5)
		|| (!ft_strncmp("env", cmd, 3) && ft_strlen(cmd) == 3)
		|| (!ft_strncmp("exit", cmd, 4) && ft_strlen(cmd) == 4))
		tiny->is_builtin = true;
	else
		tiny->is_builtin = false;
}

void	run_builtin(t_tiny *tiny)
{
	if (!ft_strncmp(tiny->tokens[0], "exit", 4))
		ft_exit(tiny);
	if (!ft_strncmp(tiny->tokens[0], "pwd", 3))
		ft_pwd(tiny);
	if (!ft_strncmp(tiny->tokens[0], "echo", 4))
		ft_echo(tiny);
	if (!ft_strncmp(tiny->tokens[0], "cd", 2))
		ft_cd(tiny);
	if (!ft_strncmp(tiny->tokens[0], "env", 3))
		ft_env(tiny);
	if (!ft_strncmp(tiny->tokens[0], "export", 6))
		ft_export(tiny);
	if (!ft_strncmp(tiny->tokens[0], "unset", 5))
		ft_unset(tiny);
}
