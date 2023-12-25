/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_reverse_alphabet.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:19:19 by tales             #+#    #+#             */
/*   Updated: 2023/09/15 16:58:31 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>

void ft_print_reverse_alphabet(void);

int main(int ac, char **av)
{
  ft_print_reverse_alphabet();
  return (0);
}

void ft_putchar(char c)
{
  write(1 ,&c, 1);
}

void ft_print_reverse_alphabet(void)
{
  char z = 'z';

  while(z >= 'a')
  {
    ft_putchar(z);
    z--;
  }
  ft_putchar('\n');

}
