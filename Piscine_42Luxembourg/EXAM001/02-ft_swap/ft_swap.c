/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ######.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmarti <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:19:19 by tales             #+#    #+#             */
/*   Updated: 2022/09/25 16:58:31 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>

void	ft_swap(int *a, int *b);

int	main (void)
{
	int	a;
	int	b;
	
	a = 25;
	b = 50;
	
	printf("Valor Antes\n A :%d, B: %d" ,a , b);
	
	printf("\n");
	printf("\n");
	ft_swap(&a,&b);
	
	printf("Valor Depois\n A :%d, B: %d",a , b);
	printf("\n");

}


void	ft_swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}
