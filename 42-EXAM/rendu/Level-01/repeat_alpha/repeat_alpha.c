/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repeat_alpha.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 11:26:48 by tales             #+#    #+#             */
/*   Updated: 2024/07/14 14:21:15 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	repeat_alpha(char *str)
{
	char	*alpha;
	int		i;
	int		j;

	i = 0;
	alpha = "abcdefghijklmnopqrstuvwxyz";
	while (str[i] != '\0')
	{
		j = 0;
		if ((str[i] >= 'a' && str[i] <= 'z')||(str[i] >= 'A' && str[i] <= 'Z'))
		{
			while (str[i] != alpha[j])
			{
				ft_putchar(str[i]);
				j++;
			}

		}
        ft_putchar(str[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		repeat_alpha(av[1]);
	}
	else
		ft_putchar('\n');
	return (0);
}