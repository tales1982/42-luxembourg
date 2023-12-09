/*
 • Escreva uma função que exiba um número passado como parâmetro. A função
   deverá ser capaz de mostrar a totalidade dos valores possíveis em uma variável de
   tipo int.
• Ela deverá ser prototipada da seguinte maneira:
   void ft_putnbr(int nb).
   Funções autorizadas : write
*/

#include <unistd.h>

void	ft_putchar(char str);
void	ft_putnbr(int nb);

int	main(int argc, char **argv)
{
	int n = 42;
	
	ft_putnbr(n);
	ft_putchar('\n');
	return(0);
}

void	ft_putchar(char str)
{
  write(1, &str,1);
}

void	ft_putnbr(int nb)
{

	char	digit;
	if(nb < 0)
	{
		ft_putchar('-');
		nb = -nb;	
	}
	if(nb >= 10)
	{
		ft_putnbr(nb / 10);
	}
	digit = nb % 10 + '0';
  	ft_putchar(digit);
}
