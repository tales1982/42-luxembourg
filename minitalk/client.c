#include "minitalk.h"

void	send_char(pid_t server_pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if (c & (1 << i))
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		usleep(100);
		i--;
	}
	
	
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;
	char	*message;

	if (argc != 3)
	{
		write(2, "Usage: ./client [server PID] [message]\n", 40);//alterar para usar o ft_putstr
		return (1);
	}
	server_pid = atoi(argv[1]);//alterar para usar o ft_atoi
	message = argv[2];
	while (*message != '\0')
	{
		send_char(server_pid, *message);
		message++;
	}

	return (0);
}

