#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h> // Para definir pid_t

# include "libft/libft.h" // Inclui a libft para usar as funções ft_*

// Funções do servidor
void	handle_signal(int sig, siginfo_t *info, void *context);

// Funções do cliente
void	send_char(pid_t server_pid, char c);

#endif
