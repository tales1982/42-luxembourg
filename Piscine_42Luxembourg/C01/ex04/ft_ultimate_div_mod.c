/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_div_mod.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 14:10:19 by tales             #+#    #+#             */
/*   Updated: 2023/12/16 14:28:01 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
Funções permitidas: Nenhuma
• Crie uma função ft_ultimate_div_mod com o seguinte protótipo:
void ft_ultimate_div_mod(int *a, int *b);
• Esta função divide os parâmetros a por b. O resultado desta divisão é armazenado no
int apontado por a. O restante da divisão é armazenado no int apontado por b.
*/

#include <stdio.h>

void ft_ultimate_div_mod(int *a, int *b);

int main()
{
    int a;
    int b;

    a = 10;
    b = 2;

    ft_ultimate_div_mod(&a, &b);
    printf("%d\n",a);
    printf("%d\n",b);
    return(0);
}

void ft_ultimate_div_mod(int *a, int *b)
{
    int temp;

    temp = *a;

    *a = temp / *b;
    *b = temp % *b;
}