/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:19:19 by tales             #+#    #+#             */
/*   Updated: 2023/12/15 16:58:31 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
 Crie uma função que receba um ponteiro para int como parâmetro e defina o valor "42"
 para aquele int.
 • Veja como deve ser prototipado:
 void ft_ft(int *nbr);
*/
#include <stdio.h>

void	ft_ft(int *nbr);

int	main(int ac, char **ag)
{
	int n = 1;
	ft_ft(&n);
	printf("%d",n);
	return(0);
}

void	ft_ft(int *nbr)
{
	*nbr = 42;	
}
