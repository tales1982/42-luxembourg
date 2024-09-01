/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_alphabet.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:37:26 by tales             #+#    #+#             */
/*   Updated: 2024/09/01 16:44:03 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c00.h"

// Version 01
void	ft_print_alphabet(void)
{
	write(1, "abcdefghijklmnopqrstuvwxyz", 26);
}

// Version 02
void	ft_print_alphabet_v2(void)
{
	char a;

	a = 'a';
	while (a <= 'z')
	{
		write(1, &a, 1);
		a++;
	}
}