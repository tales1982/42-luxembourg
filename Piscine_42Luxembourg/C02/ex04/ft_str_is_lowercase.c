/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_lowercase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 11:03:05  by tales            #+#    #+#             */
/*   Updated: 2023/12/17 11:20:16  by tales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
 Funções autorizadas : Nenhuma
 Escreva uma função que retorne 1 se a string passada como parâmetro só contiver
 caracteres alfabéticos minúsculos e retorne 0 se a função contiver outros tipos de
 caracteres.
 Ela deverá ser prototipada da seguinte maneira:
 int ft_str_is_lowercase(char *str);
 Ela deverá retornar 1 se str for uma string vazia.
*/
#include <stdio.h>
int ft_str_is_lowercase(char *str);

 int main(void)
{
     char str[] = "jk";

  int res;

  res = ft_str_is_lowercase(str);

  printf("%d\n",res);
  //return(0);
}

 int ft_str_is_lowercase(char *str)
 {
    while(*str != '\0')
    {
        if(!(*str >='a' && *str <= 'z'))
        {
            return(0);
        }
        str++;
        
    }
    return(1);
 }