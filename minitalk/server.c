#include "minitalk.h"
#include "./libft.h"

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
		ft_putchar_fd(character,1); // Usar ft_putchar para imprimir o caractere
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

	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1) {
		ft_putstr_fd("Error: Failed to set signal handlers\n", 2);
		return (1);
	}

	ft_putstr_fd("Server PID: ",1); // Usar ft_putstr para imprimir o texto
	pid_t pid = getpid();
	ft_putnbr_fd(pid, 1); // Usar ft_putnbr_fd para imprimir o PID
	ft_putchar_fd('\n',1); // Usar ft_putchar para imprimir uma nova linha

	while (1)
	{
		pause();
	}
	return (0);
}

