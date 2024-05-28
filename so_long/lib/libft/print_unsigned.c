/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 16:03:30 by tlima-de          #+#    #+#             */
/*   Updated: 2024/03/13 18:55:52 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	convert_num(unsigned int nb)
{
	if (nb > 9)
		print_unsigned(nb / 10);
	if (nb <= 9)
	{
		ft_putchar_fd(nb + 48, 1);
		return ;
	}
	ft_putchar_fd((nb % 10) + 48, 1);
}

int	print_unsigned(unsigned int nb)
{
	unsigned int	i;

	convert_num(nb);
	i = 1;
	while (nb > 9)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}
