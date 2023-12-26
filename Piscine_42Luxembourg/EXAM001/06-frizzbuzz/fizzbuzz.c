/*
Assignment name  : fizzbuzz
Expected files   : fizzbuzz.c
Allowed functions: write
--------------------------------------------------------------------------------

Ecrire un programme qui écrit une suite de nombres de 1 à 100 sur la sortie 
standard, tous séparés par une newline. 

Si le nombre est un multiple de 3, le programme doit écrire 'fizz' à la place.

Si le nombre est un multiple de 5, le programme doit écrire 'buzz' à la place.

Si le nombre est un multiple de 3 et un multiple de 5, le programme doit écrire 
'fizzbuzz' à la place.

Exemple:

$>./fizzbuzz
1
2
fizz
4
buzz
fizz
7
8
fizz
buzz
11
fizz
13
14
fizzbuzz
[...]
97
98
fizz
buzz
$>
*/

#include <unistd.h>

void	ft_putchar(char str);
void	ft_putnbr(int nb);
void	ft_frizzbuzz(int nb);

int	main(int argc, char **argv)
{
	ft_frizzbuzz(1);
	
}

void	ft_putchar(char str)
{
	write(1, &str, 1);
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
	digit = nb % 10 + 48;
	ft_putchar(digit);
}

void	ft_frizzbuzz(int n)
{
	while(n <= 100)
	{
		
		if(n % 3 == 0 && n % 5 == 0)
		{
			write(1,"fizzbuzz",8);
			write(1,"\n",1);
			n++;
		}
		else if(n % 3 == 0)
		{
			write(1,"fizz",4);
			write(1,"\n",1);
			n++;
		}
		else if(n % 5 == 0)
		{
			write(1,"buzz",4);
			write(1,"\n",1);
			n++;
		}
		else
		{
		ft_putnbr(n);
		ft_putchar('\n');
		n++;
		}
	}
	
}