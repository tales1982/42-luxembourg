/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_comb2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:19:19 by tales             #+#    #+#             */
/*   Updated: 2023/12/15 16:58:31 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
 Crie uma função que exiba todas as combinações diferentes de dois números de dois dígitos
 (XX XX) entre 00 e 99, listados em ordem crescente.
 Aqui está o resultado esperado:
 $>./a.out | gato -e
 00 01, 00 02, 00 03, 00 04, 00 05, ..., 00 99, 01 02, ..., 97 99, 98 99$>
 Veja como deve ser prototipado:
 • void ft_print_comb2(void);
 */
#include <unistd.h>

void	ft_print_comb2(void);

int	main(int ac, char **av)
{
	ft_print_comb2();
	return(0);
}

void ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_print_comb2(void)
{
	int	a;
	int	b;
	int	c;
	int	d;

	a = 0;
	b = 1;

	while (a < 99)
	{	
		b = a + 1;
		while(b <= 99)
		{
			ft_putchar(a / 10 + '0');
			ft_putchar(a % 10 + '0');
			ft_putchar(' ');
			ft_putchar(b / 10 + '0');	
			ft_putchar(b % 10 + '0');
			if (a / 10 != 9 || a % 10 != 8)
			{
			ft_putchar(',');
			ft_putchar(' ');	
			}
		b++;
		}
	a++;
	}
}