/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:49:03 by tales             #+#    #+#             */
/*   Updated: 2024/09/06 22:10:10 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c01.h"

int	main(void)
{
	// printf(GREEN "####  version-1  ####\033[0m\n");
	// printf(GREEN "####  version-2  ####\033[0m\n");
	printf(YELLOW "******************** 00 : ft_ft ******************************\033[0m\n");
	int a;
	ft_ft(&a); // Passa o endereço de 'a' para a função
	printf("%d", a);
	printf("\n");
	printf("\n");
	printf(YELLOW "******************** 01 : ft_ultimate_ft **********************\033[0m\n");
	int n = 0;
	int *p1 = &n;
	int **p2 = &p1;
	int ***p3 = &p2;
	int ****p4 = &p3;
	int *****p5 = &p4;
	int ******p6 = &p5;
	int *******p7 = &p6;
	int ********p8 = &p7;
	ft_ultimate_ft(&p8);
	printf("%d\n", n);
	printf("\n");
	printf(YELLOW "******************** 02 : ft_swap ****************************\033[0m\n");
	int swap_a = 10;
	int swap_b = 20;
	printf("A = %d **** B = %d \n", swap_a, swap_b);
	ft_swap(&swap_a, &swap_b);
	printf("A = %d **** B = %d \n", swap_a, swap_b);
	printf("\n");
	printf("\n");
	printf(YELLOW "******************** 03 : ft_div_mod *************************\033[0m\n");
	int div_mod_a = 10;
	int div_mod_b = 3;
	int div;
	int mod;
	ft_div_mod(div_mod_a, div_mod_b, &div, &mod);
	printf("Divisão: %d, Resto: %d\n", div, mod);
	printf("\n");
	printf("\n");
	printf(YELLOW "******************** 04 : ft_ultimate_div_mod ****************\033[0m\n");
	// ft_ultimate_div_mod();
	printf("\n");
	printf("\n");
	printf(YELLOW "******************** 05 : ft_putstr **************************\033[0m\n");
	// ft_putstr();
	printf("\n");
	printf("\n");
	printf(YELLOW "******************** 06 : ft_strlen **************************\033[0m\n");
	// ft_strlen();
	printf("\n");
	printf("\n");
	printf(YELLOW "******************** 07 : ft_rev_int_tab *********************\033[0m\n");
	// ft_rev_int_tab();
	printf("\n");
	printf("\n");
	printf(YELLOW "******************** 08 : ft_sort_int_tab ********************\033[0m\n");
	// ft_sort_int_tab();
	printf("\n");
	printf("\n");

	return (0);
}