/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_power_of_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:26:09 by tales             #+#    #+#             */
/*   Updated: 2024/07/31 16:35:37 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>

int	    is_power_of_2(unsigned int n)
{
    while (n > 1)
    {
        if(n % 2 == 0)
            n = n / 2;//dividi ate chegar em 1 
        else
            return(0);//se na divisao tiver reto retorna 0
    }
    return(1);
    
}

int	main(void)
{
 	printf("%d\n", is_power_of_2(1024));
 	printf("%d\n", is_power_of_2(1023));
 	printf("%d\n", is_power_of_2(0));
 	printf("%d\n", is_power_of_2(1));
 }