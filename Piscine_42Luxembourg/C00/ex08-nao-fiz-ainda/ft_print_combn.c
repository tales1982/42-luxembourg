/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_combn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:19:19 by tales             #+#    #+#             */
/*   Updated: 2023/12/15 16:58:31 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
 Funções permitidas: write
 • Crie uma função que exiba todas as combinações diferentes de n números em ordem crescente
 ordem.
 • n será tal que: 0 < n < 10.
 • Se n = 2, aqui está o resultado esperado:
 $>./a.out | gato -e
 01, 02, 03, ..., 09, 12, ..., 79, 89$>
 • Veja como deve ser prototipado:
 void ft_print_combn(int n);
 */
#include <unistd.h>

void	ft_print_combn(int n);

int	main(int ac, char **av)
{
	ft_print_combn(2);
	write(1,"\n",1);
	return(0);
}

void	ft_print_combn(int n)
{
	
}
