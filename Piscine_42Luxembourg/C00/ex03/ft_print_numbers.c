/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_numbers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:19:19 by tales             #+#    #+#             */
/*   Updated: 2023/12/15 16:58:31 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
 Crie uma função que exiba todos os dígitos, em uma única linha, em ordem crescente.
 Veja como deve ser prototipado:
 • void ft_print_numbers(void);
*/
#include <unistd.h>

void ft_print_numbers(void);

int main(int ac, char **av)
{
  ft_print_numbers();
  return (0);
}

void ft_putchar(char c)
{
  write(1,&c,1);
}

void ft_print_numbers(void)
{
  char nb;

  nb = '0';
  while(nb <= '9')
  {
   ft_putchar(nb);
   nb++;
  }
  ft_putchar('\n');
}