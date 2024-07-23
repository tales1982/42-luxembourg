/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:07:04 by tales             #+#    #+#             */
/*   Updated: 2024/07/23 22:15:36 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_atoi(const char *str)
{
    int i;
    int sign;
    int res;

    i = 0; 
    sign = 1;
    res = 0;
    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
        i++;
    if(str[i] == '-' || str[i] == '+')
    {
        if(str[i] == '-')
            sign *= -1;
        i++;
    }
    while (str[i] >='0' && str[i] <= '9')
    {
        res = res * 10 +(str[i] - '0');
        i++;
    }
    return(res * sign);    
}

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        printf("ft_atoi(\"%s\") = %d\n", argv[1], ft_atoi(argv[1]));
    }
    else
    {
        printf("Usage: ./a.out <number>\n");
    }
    return (0);
}