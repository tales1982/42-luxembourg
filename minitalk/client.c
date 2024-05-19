#include "minitalk.h"

void	send_char(pid_t server_pid, char c)
{
	int	i;
	int res;

	i = 7;
	while (i >= 0)
	{
		if (c & (1 << i))
			res = kill(server_pid, SIGUSR2);
		else
			res = kill(server_pid, SIGUSR1);
		
		if (res == -1)
		{
			perror("kill");
			exit(EXIT_FAILURE);
		}
		
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
		ft_putstr_fd("Usage: ./client [server PID] [message]\n", 2);
		return (1);
	}

	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
	{
		ft_putstr_fd("Error: Invalid server PID\n", 2);
		return (1);
	}

	message = argv[2];
	while (*message != '\0')
	{
		send_char(server_pid, *message);
		message++;
	}

	return (0);
}
