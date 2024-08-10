/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_capitalizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 10:26:10 by tales             #+#    #+#             */
/*   Updated: 2024/08/03 12:00:19 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	capitalize_word(char *s)
{
	int new_word = 1;

	while (*s)
	{
		if (*s == ' ' || *s == '\t')
		{
			new_word = 1;
			ft_putchar(*s);
		}
		else
		{
			if (new_word && *s >= 'a' && *s <= 'z')
				ft_putchar(*s - 32);
			else if (!new_word && *s >= 'A' && *s <= 'Z')
				ft_putchar(*s + 32);
			else
				ft_putchar(*s);
			new_word = 0;
		}
		s++;
	}
}

int	main(int ac, char **av)
{
	int i = 1;

	if (ac > 1)
	{
		while (i < ac)
		{
			capitalize_word(av[i]);
            ft_putchar('\n');
			i++;
		}
	}
    else
	    ft_putchar('\n');
	return (0);
}
