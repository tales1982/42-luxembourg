/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_negative.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:19:19 by tales             #+#    #+#             */
/*   Updated: 2023/12/15 16:58:31 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
 Crie uma função que exiba ‘N’ ou ‘P’ dependendo do sinal do inteiro inserido
 como parâmetro. Se n for negativo, exiba 'N'. Se n for positivo ou nulo, exiba 'P'.
 Veja como deve ser prototipado:
 • void ft_is_negative(int n);
*/

#include <unistd.h>

void ft_is_negative(int n);

int main(int ac, char **av)
{
  int nb;
  nb = 1;
    ;
  ft_is_negative(nb);
}

void ft_putchar(char c)
{
  write(1, &c, 1);
}

void ft_is_negative(int n)
{
  if(n >= 0)
  {
    ft_putchar('P');
  }
  else
  {
    ft_putchar('N');
  }
  ft_putchar('\n');
}
