/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmarti <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:19:19 by tales             #+#    #+#             */
/*   Updated: 2022/09/25 16:58:31 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
 Escreva uma função que exiba o caractere passado como parâmetro.
 Será prototipado da seguinte forma:
 • void ft_putchar(char c);
 Para exibir o caractere, você deve usar a função de gravação da seguinte forma
*/
#include <unistd.h>

void ft_putchar(char c);

int main(int ac, char **av)
{
  char str[] = "42 Luxembourg";
  int i;

  i = 0;
  while(str[i] != '\0')
  {
    ft_putchar(str[i]);
    i++;
  }
  ft_putchar('\n');

}

void ft_putchar(char c)
{
  write(1, &c, 1);
}