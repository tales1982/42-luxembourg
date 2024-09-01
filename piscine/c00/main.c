/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:13:09 by tales             #+#    #+#             */
/*   Updated: 2024/09/01 16:43:22 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c00.h"

int	main(void)
{
	printf(YELLOW "******************** 00 : ft_Puchar ********************\033[0m\n");
	char c = 'A';
	ft_putchar(c);
	ft_putchar('\n');
	ft_putchar('\n');
	printf(YELLOW "**************** 01 : ft_print_alphabet ****************\033[0m\n");
	printf(GREEN "####  version-1  ####\033[0m\n");
	ft_print_alphabet();
	ft_putchar('\n');
	printf(GREEN "####  version-2  ####\033[0m\n");
	ft_print_alphabet_v2();
	ft_putchar('\n');
	ft_putchar('\n');
	printf(YELLOW "************ 02 : ft_print_reverse_alphabet ************\033[0m\n");
	printf(GREEN "####  version-1  ####\033[0m\n");
	ft_print_reverse_alphabet();
	ft_putchar('\n');
	printf(GREEN "####  version-2  ####\033[0m\n");
	ft_print_reverse_alphabet_v2();
	ft_putchar('\n');
	ft_putchar('\n');
	printf(YELLOW "***************** 03 : ft_print_numbers ****************\033[0m\n");
	ft_print_numbers();
	ft_putchar('\n');
	ft_putchar('\n');
	printf(YELLOW "***************** 04 : ft_is_negative ******************\033[0m\n");
	ft_is_negative(-10);
	ft_putchar('\n');
	ft_is_negative(10);
	ft_putchar('\n');
	ft_is_negative(0);
	ft_putchar('\n');
	ft_putchar('\n');
	printf(YELLOW "***************** 05 : ft_print_comb ******************\033[0m\n");
	ft_print_comb();
	ft_putchar('\n');
	ft_putchar('\n');
	printf(YELLOW "***************** 06 : ft_print_comb2 ******************\033[0m\n");
	ft_print_comb2();
	ft_putchar('\n');
	ft_putchar('\n');
	printf(YELLOW "***************** 07 : ft_putnbr ***********************\033[0m\n");
	ft_putnbr(42);
	ft_putchar('\n');
	ft_putchar('\n');
	printf(YELLOW "***************** 08 : ft_print_combn ******************\033[0m\n");
	ft_print_combn(2);
	ft_putchar('\n');
	ft_putchar('\n');

	return (0);
}