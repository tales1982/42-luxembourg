/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 22:04:36 by tales             #+#    #+#             */
/*   Updated: 2024/07/31 23:17:20 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>

int ft_len(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
        i++;
    return(i);
}

void ft_union(char *str1, char *str2)
{
    int i;
    char *aux;

    i = 0;
    aux = (char *)malloc(sizeof(char) * ft_len(str2 + 1));
}
