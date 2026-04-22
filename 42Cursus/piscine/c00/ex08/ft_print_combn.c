/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_combn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 21:36:05 by tales             #+#    #+#             */
/*   Updated: 2024/09/01 16:43:31 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c00.h"

void ft_printnbr(int nb)
{
    char c;

    if (nb / 10 > 0)
        ft_printnbr(nb / 10);
    c = nb % 10 + '0';
    write(1, &c, 1);
}

void print_comb(int *arr, int n)
{
    int i;

    i = 0;
    while (i < n)
    {
        char c = arr[i] + '0';
        write(1, &c, 1);
        i++;
    }
    if (arr[0] != 10 - n) // Para evitar a última vírgula
        write(1, ", ", 2);
}

void generate_combinations(int *arr, int n, int index, int start)
{
    if (index == n)
    {
        print_comb(arr, n);
        return;
    }
    while (start <= 9)
    {
        arr[index] = start;
        generate_combinations(arr, n, index + 1, start + 1);
        start++;
    }
}

void ft_print_combn(int n)
{
    int arr[9]; // Um array para armazenar as combinações
    generate_combinations(arr, n, 0, 0);
}

