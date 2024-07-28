/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 21:09:01 by tales             #+#    #+#             */
/*   Updated: 2024/07/23 21:59:36 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int	ft_atoi(char *str)
{
	int	i;
	int	res;
	int	sinal;

	sinal = 1;
	res = 0;
	i = 0;
	while (str[i] == ' ' || str[i] >= 9 && str[i] <= 13)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sinal *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * sinal);
}

int	main(int ac, char **av)
{
	int n1;
	int n2;
	// int res;

	if (ac == 4)
	{
		n1 = ft_atoi(av[1]);
		n2 = ft_atoi(av[3]);
		if (av[2][0] == '+')
			printf("%d", n1 + n2);
		else if (av[2][0] == '-')
			printf("%d", n1 - n2);
		if (av[2][0] == '/')
			printf("%d", n1 / n2);
		else if (av[2][0] == '*')
			printf("%d", n1 * n2);
		printf("\n");
	}
	else
		write(1, "\n", 1);
	return (0);
}