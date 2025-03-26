/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-fif <luis-fif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 10:24:49 by luis-fif          #+#    #+#             */
/*   Updated: 2024/11/04 16:30:50 by luis-fif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	if (n < 0 && n != -2147483648)
	{
		ft_putchar_fd('-', fd);
		n = n * -1;
	}
	if (n <= 9 && n >= 0)
		ft_putchar_fd(n + 48, fd);
	else if (n > 0)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd(n % 10 + 48, fd);
	}
}

int	count_digits(int n)
{
	int	n_digits;

	n_digits = 0;
	if (n < 0)
		n = n * -1;
	while (n > 0)
	{
		n = n / 10;
		n_digits++;
	}
	return (n_digits);
}

int	power(int n_digits)
{
	int	p10;

	p10 = 1;
	while (n_digits > 0)
	{
		p10 = p10 * 10;
		n_digits--;
	}
	return (p10);
}

char	*ft_itoa(int n)
{
	char	*itoa;
	int		p10;
	int		i;

	itoa = (char *)malloc((count_digits(n) + 2) * sizeof(char));
	if (!itoa)
		return (NULL);
	if (n == -2147483648)
		return (substr_ft("-2147483648", 0, 11));
	i = 0;
	if (n < 0)
	{
		itoa[i++] = '-';
		n = n * (-1);
	}
	p10 = power(count_digits(n) - 1);
	while (p10 > 0)
	{
		itoa[i++] = (n / p10 % 10 + 48);
		p10 = p10 / 10;
	}
	itoa[i] = '\0';
	return (itoa);
}
