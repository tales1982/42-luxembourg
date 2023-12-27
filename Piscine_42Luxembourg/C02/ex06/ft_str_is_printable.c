/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_uppercase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 11:13:25  by tales            #+#    #+#             */
/*   Updated: 2023/12/17 11:17:22  by tales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
  Funções autorizadas : Nenhuma
  Escreva uma função que retorne 1 se a string passada como parâmetro só contiver
  caracteres imprimíveis e retorne 0 se a função contiver outros tipos de caracteres.
  Ela deverá ser prototipada da seguinte maneira:
  int ft_str_is_printable(char *str);
  Ela deverá retornar 1 se str for uma string vazia.
*/

#include <stdio.h>
int ft_str_is_printable(char *str);

int main(void)
{
     char str[] = "\t \a";

  int res;

  res = ft_str_is_printable(str);

  printf("%d\n",res);
  //return(0);
}

int ft_str_is_printable(char *str)
{
    while(*str != '\0')
    {
        if(*str >=0 && *str <=31)
        {
            return(0);
        }
        str++;
    }
    return(1);
}