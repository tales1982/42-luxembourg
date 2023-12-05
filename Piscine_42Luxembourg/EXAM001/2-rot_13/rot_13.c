/*
Assignment name  : rot_13
Expected files   : rot_13.c
Allowed functions: write
--------------------------------------------------------------------------------
Escreva um programa que pegue uma string e a exiba, substituindo cada uma de suas
letras por letra, 13 espaços à frente em ordem alfabética.

'z' torna-se 'm' e 'Z' torna-se 'M'. O caso permanece inalterado.

A saída será seguida por uma nova linha.

Se o número de argumentos não for 1, o programa exibe uma nova linha.
Example:

$>./rot_13 "abc"
nop
$>./rot_13 "My horse is Amazing." | cat -e
Zl ubefr vf Nznmvat.$
$>./rot_13 "AkjhZ zLKIJz , 23y " | cat -e
NxwuM mYXVWm , 23l $
$>./rot_13 | cat -e
$
$> 
*/
//=================================================================
#include <stdio.h>

char	*ft_rot13(char *str);

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("ERRO: Nenhum argumento fornecido!\n");
		return (1);
	}
	else
	{
		printf("%s", ft_rot13(argv[1]));
	}
	return (0);
}

char	*ft_rot13(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] >= 'a' && str[i] <= 'n')
			|| (str[i] >= 'A' && str[i] <= 'N'))
		{
			str[i] += 13;
		}
		else if ((str[i] >= 'm' && str[i] <= 'z')
			|| (str[i] >= 'M' && str[i] <= 'Z'))
		{
			str[i] -= 13;
		}
		i++;
	}
	return (str);
}
