/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 16:53:09 by tales             #+#    #+#             */
/*   Updated: 2024/07/21 12:22:38 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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
		i++;
	return (i);
}

void	rev_print(char *str)
{
	int		i;
	int		len;
	char	*dest;

	len = ft_len(str);
	dest = (char *)malloc((len + 1) * sizeof(char));
	if (dest == NULL)
	{
		write(1, "ERRO", 4);
		return ;
	}
	i = 0;
	while (len > 0)
		dest[i++] = str[--len];
	dest[i] = '\0';
	i = 0;
	while (dest[i] != '\0')
	{
		ft_putchar(dest[i]);
		i++;
	}
	free(dest);
}

int	main(int ac, char **av)
{
	int		len;
	int		i;
	char	*str;

	if (ac == 2)
	{
		rev_print(av[1]);
	}
	else
	{
		ft_putchar('\n');
	}
	return (0);
}
