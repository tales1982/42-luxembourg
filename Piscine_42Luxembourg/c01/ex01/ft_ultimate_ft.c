/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_ft.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:19:19 by tales             #+#    #+#             */
/*   Updated: 2023/12/15 16:58:31 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
 Crie uma função que leva um ponteiro para ponteiro para ponteiro para ponteiro para ponteiro
 para ponteiro para ponteiro para ponteiro para ponteiro para int como parâmetro e define o valor
 "42" para esse int.
 • Veja como deve ser prototipado:
 void ft_ultimate_ft(int *********nbr);
*/

#include <stdio.h>
void ft_ultimate_ft(int *********nbr);

int main() {
    int num = 0;
    int *ptr1 = &num;
    int **ptr2 = &ptr1;
    int ***ptr3 = &ptr2;
    int ****ptr4 = &ptr3;
    int *****ptr5 = &ptr4;
    int ******ptr6 = &ptr5;
    int *******ptr7 = &ptr6;
    int ********ptr8 = &ptr7;
    int *********ptr9 = &ptr8;

    ft_ultimate_ft(ptr9);

    printf("Valor alterado para: %d\n", *********ptr9);

    return 0;
}

void ft_ultimate_ft(int *********nbr)
{
	*********nbr = 42;
}
