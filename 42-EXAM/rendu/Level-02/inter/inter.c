/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:19:58 by tales             #+#    #+#             */
/*   Updated: 2024/07/28 17:25:39 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int		check(char *str, char c, int pos)
{
	int	i;

	i = 0;
	while (i < pos)
	{
		if (str[i] == c)
			return (0);
		i++;
	}
	return (1);
}

void	inter(char *str1, char *str2)
{
	int	i;
	int	j;
	int	k;
	char	aux[256];

	k = 0;
	i = 0;
	while (str1[i] != '\0')
	{
		j = 0;
		while (str2[j] != '\0')
		{
			if (str1[i] == str2[j])
			{
				if (check(aux, str1[i], k))
				{
					aux[k] = str1[i];
					k++;
				}
				break ;
			}
			j++;
		}
		i++;
	}
	aux[k] = '\0';
	i = 0;
	while (aux[i] != '\0')
	{
		ft_putchar(aux[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	if (argc == 3)
	{
		inter(argv[1], argv[2]);
	}
	ft_putchar('\n');
	return (0);
}
