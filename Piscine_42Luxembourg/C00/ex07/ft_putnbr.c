/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:19:19 by tales             #+#    #+#             */
/*   Updated: 2023/12/15 16:58:31 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
  Funções permitidas: write
  • Crie uma função que exiba o número inserido como parâmetro. A função
  deve ser capaz de exibir todos os valores possíveis dentro de uma variável do tipo int.
  • Veja como deve ser prototipado:
  void ft_putnbr(int nb);
  • Por exemplo:
  ◦ ft_putnbr(42) exibe "42".
 */
#include <unistd.h>

void	ft_putnbr(int nb);

int	main(int ac, char **av)
{
	ft_putnbr(42);
	write(1, "\n", 1);
	return(0);
}

void	ft_putnbr(int nb)
{
	char	digit;

	if (nb >= 10)
	{
		ft_putnbr(nb / 10);
		
	} 
	
	digit = nb % 10 + '0';
	write(1, &digit, 1);
}
