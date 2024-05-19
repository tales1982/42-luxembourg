#include "minitalk.h"

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static int	bit_count = 0;
	static char	character = 0;

	(void)info;    // Marcar o parâmetro 'info' como não utilizado
	(void)context; // Marcar o parâmetro 'context' como não utilizado

	if (sig == SIGUSR1)
		character = (character << 1) | 0;  
	else if (sig == SIGUSR2)
		character = (character << 1) | 1;  
	
	bit_count++;
	
	if (bit_count == 8)
	{
		write(1, &character, 1);//alterar para usar o ft_putchar
		bit_count = 0;
		character = 0;
	}
}

int	main(void)
{
	struct sigaction sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_signal;
	sigemptyset(&sa.sa_mask);

	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	write(1, "Server PID: ", 12);//alterrar para usar o ft_putstr
	pid_t pid = getpid();
	char pid_str[12];
	sprintf(pid_str, "%d\n", pid);
	write(1, pid_str, strlen(pid_str));//alterar para usar o ft_putstr e o ft_strlen

	while (1)
	{
		pause();
	}
	return (0);
}

