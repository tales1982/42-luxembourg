/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_and_replace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:41:21 by tales             #+#    #+#             */
/*   Updated: 2024/07/21 15:40:01 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
    write(1, &c, 1);
}

int	ft_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

void replace(char *s1, char old_char, char new_char)
{
	int	i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] == old_char)
			ft_putchar(new_char);
		else
			ft_putchar(s1[i]);

		i++;
	}
}
int main(int ac, char **av)
{
    if (ac == 4 && av[2][1] == '\0' && av[3][1] == '\0')
    {
        replace(av[1], av[2][0], av[3][0]);
    }
    else
    {
        ft_putchar('\n');
    }

    return 0;
}