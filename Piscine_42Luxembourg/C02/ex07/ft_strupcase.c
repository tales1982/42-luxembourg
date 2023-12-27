/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strupcase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 11:23:15  by tales            #+#    #+#             */
/*   Updated: 2023/12/17 11:27:29  by tales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
  Funções autorizadas : Nenhuma
  Escreva uma função que deixe todas as letras em maiúsculo.
  Ela deverá ser prototipada da seguinte maneira:
  char *ft_strupcase(char *str);
  Ela deverá retornar str.
*/

#include <stdio.h>

char *ft_strupcase(char *str);

 int main(void)
{
    char str[] = "tales lima";
    char *res;

  res = ft_strupcase(str);

   
    printf("%s\n",res);
  return(0);
}

char	*ft_strupcase(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
		{
			str[i] -= 32;
		}
		i++;
	}
	return (str);
}