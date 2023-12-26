/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_alphabet.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:19:19 by tales             #+#    #+#             */
/*   Updated: 2022/09/25 16:58:31 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
 Crie uma função que exiba o alfabeto em letras minúsculas, em uma única linha, por
 ordem crescente, começando pela letra ‘a’.
 Veja como deve ser prototipado:
 • void ft_print_alphabet(void);
*/
#include <unistd.h>

void ft_print_alphabet(void);

int main(int ac, char **av)
{
  ft_print_alphabet();
}

void ft_putchar(char c)
{
  write(1, &c, 1);
}

void ft_print_alphabet(void)
{
  char a = 'a';

  while( a <= 'z')
  {
    ft_putchar(a);
    a++;
  }
ft_putchar('\n');
}