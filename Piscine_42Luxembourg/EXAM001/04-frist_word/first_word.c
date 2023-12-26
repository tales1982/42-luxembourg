/*
 Escreva um programa que receba uma string e exiba sua primeira palavra, seguida por uma
nova linha.

Uma palavra é uma seção de string delimitada por espaços/tabulações ou pelo início/fim de
a corda.

Se o número de parâmetros não for 1, ou se não houver palavras, basta exibir
uma nova linha.

Exemplos:

$> ./first_word "FOR PONY" | cat -e
FOR$
$> ./first_word "this        ...       is sparta, then again, maybe    not" | cat -e
this$
$> ./first_word "   " | cat -e
$
$> ./first_word "a" "b" | cat -e
$
$> ./first_word "  lorem,ipsum  " | cat -e
lorem,ipsum$
$>
*/
#include <stdio.h>

int	main(int argc, char *argv[])
{
	char	*input;
	int	found;
	
	input = argv[1];
	found = 0;

	if (argc < 2)
		return (0);
	else
	{
		while (*input != '\0')
		{
			if (*input == 'a')
			{
				printf ("a\n");
				break;
			}
			input++;
		}
	}
	if (*input != 'a')
		return (printf ("\n"));
}
