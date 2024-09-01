/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:49:03 by tales             #+#    #+#             */
/*   Updated: 2024/09/01 17:30:09 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c01.h"

int	main(void)
{
    //printf(GREEN "####  version-1  ####\033[0m\n");
    //printf(GREEN "####  version-2  ####\033[0m\n");
	printf(YELLOW "******************** 00 : ft_ft ******************************\033[0m\n");
    int a;
    ft_ft(&a);  // Passa o endereço de 'a' para a função
    printf("%d", a);
	printf("\n");
	printf("\n");
	printf(YELLOW "******************** 01 : ft_ultimate_ft **********************\033[0m\n");
	//ft_ultimate_ft();
	printf("\n");
	printf("\n");
	printf(YELLOW "******************** 02 : ft_swap ****************************\033[0m\n");
    //ft_swap();
	printf("\n");
	printf("\n");
	printf(YELLOW "******************** 03 : ft_div_mod *************************\033[0m\n");
	//ft_div_mod();
	printf("\n");
	printf("\n");
	printf(YELLOW "******************** 04 : ft_ultimate_div_mod ****************\033[0m\n");
	//ft_ultimate_div_mod();
	printf("\n");
	printf("\n");
	printf(YELLOW "******************** 05 : ft_putstr **************************\033[0m\n");
	//ft_putstr();
	printf("\n");
	printf("\n");
	printf(YELLOW "******************** 06 : ft_strlen **************************\033[0m\n");
	//ft_strlen();
	printf("\n");
	printf("\n");
	printf(YELLOW "******************** 07 : ft_rev_int_tab *********************\033[0m\n");
	//ft_rev_int_tab();
	printf("\n");
	printf("\n");
	printf(YELLOW "******************** 08 : ft_sort_int_tab ********************\033[0m\n");
	//ft_sort_int_tab();
	printf("\n");
	printf("\n");

	return (0);
}