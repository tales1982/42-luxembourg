/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_alpha.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 9:41:07  by tales             #+#    #+#             */
/*   Updated: 2023/12/17 10:18:39 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
  Funções autorizadas : Nenhuma
  Escreva uma função que retorne 1 se a string passada como parâmetro só contiver
  caracteres alfabéticos e retorne 0 se a função contiver outros tipos de caracteres.
  Ela deverá ser prototipada da seguinte maneira:
  int ft_str_is_alpha(char *str);
  Ela deverá retornar 1 se str for uma string vazia.
*/
#include <stdio.h>

int ft_str_is_alpha(char *str);

int main(void)
{
  char str[] = "tal s";

  int res;

  res = ft_str_is_alpha(str);

  printf("%d\n",res);
  return(0);
}
int	ft_str_is_alpha(char *str)
{
	while (*str)
	{
		if (!(*str >= 'A' && *str <= 'Z') && !(*str >= 'a' && *str <= 'z'))
		{
			return (0);
		}
		str++;
	}
	return (1);
}
