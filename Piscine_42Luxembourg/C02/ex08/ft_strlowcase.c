/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlowcase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 11:43:35  by tales            #+#    #+#             */
/*   Updated: 2023/12/17 11:54:07  by tales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
  Funções autorizadas : Nenhuma
  Escreva uma função que deixe todas as letras em minúsculo.
  Ela deverá ser prototipada da seguinte maneira:
  char *ft_strlowcase(char *str);
  Ela deverá retornar str.
*/

#include <stdio.h>
char *ft_strlowcase(char *str);

int main(void)
{
    char str[] = "TALES";
    char *res;

    res = ft_strlowcase(str);

    printf("%s\n", res);
    return (0);
}

char *ft_strlowcase(char *str)
{
    char *ptr;

    ptr = str;
    while(*ptr != '\0')
    {
        if(*ptr >= 'A' && *ptr <= 'Z')
        {
            *ptr += 32;
       
        }
        ptr++;
        
    }
    return(str);
}