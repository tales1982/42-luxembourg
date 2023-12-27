/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_numeric.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 10:43:45  by tales            #+#    #+#             */
/*   Updated: 2023/12/17 11:22:56  by tales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
  Funções autorizadas : Nenhuma
  Escreva uma função que retorne 1 se a string passada como parâmetro só contiver
  números e retorne 0 se a função contiver outros tipos de caracteres.
  Ela deverá ser prototipada da seguinte maneira:
  int ft_str_is_numeric(char *str);
  Ela deverá retornar 1 se str for uma string vazia.
*/
#include <stdio.h>
 int ft_str_is_numeric(char *str);

 int main(void)
{
     char str[] = "";

  int res;

  res = ft_str_is_numeric(str);

  printf("%d\n",res);
  return(0);
}

int ft_str_is_numeric(char *str)
{
    int i;

    i = 0;
    while(*str)
    {
        if(!(*str >= 48 && *str <= 57))
        {
            return(0);
        }
        str++;
    }
    return(1);
}