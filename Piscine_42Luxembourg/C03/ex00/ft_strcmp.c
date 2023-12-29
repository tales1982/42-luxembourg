/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:34:01  by tales            #+#    #+#             */
/*   Updated: 2023/12/17 12:45:47  by tales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
  Funções autorizadas : Nenhuma
• Reproduzir de forma idêntica o funcionamento da função strcmp (man strcmp).
• Ela deverá ser prototipada da seguinte maneira:
  int ft_strcmp(char *s1, char *s2);

A função strcmp em C compara duas strings e retorna um valor inteiro que
indica a relação entre essas strings.
Ela retorna um número inteiro que indica a relação entre as strings:
• Se str1 for menor que str2, retorna um valor negativo.
• Se str1 for maior que str2, retorna um valor positivo.
• Se as strings forem iguais, retorna 0.
*/

#include <stdio.h>
#include <string.h>

int ft_strcmp(char *s1, char *s2);

int main()
{
  char s1[] = "lima p";
  char s2[] = "lima paula";
  int aux;
  int aux2;

  aux = ft_strcmp(s1,s2);
  aux2 = strcmp(s1,s2);
  
  printf("AUX1..: %d\n",aux);
  printf("AUX2..: %d\n",aux2);
  return(0);
}

int ft_strcmp(char *s1, char *s2)
{

  while (*s1 && *s2 && *s1 == *s2)
  {
    s1++;
    s2++;
  }
  return(*s1 - *s2);
  
}