/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epur_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 12:07:55 by tales             #+#    #+#             */
/*   Updated: 2024/08/03 14:34:42 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	epur_str(char *str)
{
	int	i;
	int	espaco;

	i = 0;
	espaco = 0;
	while (str[i] != '\0')
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
            
		if (str[i] == '\0')
			break ;
            
		if (espaco == 1)
			ft_putchar(' ');
            
		while (str[i] && str[i] != ' ' && str[i] != '\t')
		{
			ft_putchar(str[i]);
			i++;
		}
		espaco = 1;
		i++;
	}
}

int	main(int argc, char **argv)
{
	char	*str;

	str = " this        time it      will     be    more complex  . ";
	if (argc >= 1)
	{
		epur_str(str);
		// epur_str(argv[1]);
	}
	ft_putchar('\n');
	return (0);
}
