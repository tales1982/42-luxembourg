/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_comb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:19:19 by tales             #+#    #+#             */
/*   Updated: 2023/12/15 16:58:31 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* 
 Crie uma função que exiba todas as diferentes combinações de três dígitos diferentes em
 ordem crescente, listada em ordem crescente - sim, a repetição é voluntária.
 • Aqui está o resultado pretendido:
 $>./a.out | gato -e
 012, 013, 014, 015, 016, 017, 018, 019, 023, ..., 789$>
• 987 não existe porque 789 já existe.
• 999 não existe porque o dígito 9 está presente mais de uma vez.
• Veja como deve ser prototipado:
• void ft_print_comb(void);
*/
#include <unistd.h>

void ft_print_comb(void);

int main(int ac, char **av)
{
  ft_print_comb();
  return (0);
}

void ft_putchar(char c)
{
  write(1, &c, 1);
}

void ft_print_comb(void)
{
	char	i;
	char	j;
	char	k;

	i = '0';
	j = i + 1;
	k = j + 1;
	while (i <= '7')
	{
		j = i + 1;
		while (j <= '8')
		{ 
			
			k = j + 1;
			while(k <= '9')
			{
				
				ft_putchar(i);
					ft_putchar(j);
					ft_putchar(k);
				if(i != '7')
				{
					ft_putchar(',');
					ft_putchar(' ');
				}
				k++;
			}
			
		j++;  
		} 
	i++;
	}
}
