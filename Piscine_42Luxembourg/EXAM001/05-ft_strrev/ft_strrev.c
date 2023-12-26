/*
PT:
Escreva uma função que inverte (no local) uma string.
Deve retornar seu parâmetro.
Sua função deve ser declarada da seguinte forma:

char *ft_strrev(char *str);
=================================================================
*/
#include <stdio.h>

int	ft_len(char *str);
char	*ft_strrev(char *str);

int	main(int argc, char *argv[])
{
	char	*input;
	
	
	input = argv[1];
	
	if(argc < 2)
	{
		return (printf("ERRO\n"));
	}
	else
	{	
	printf("%s\n",ft_strrev(input));
	}
}

int	ft_len(char *str)
{
	int i;
	
	i = 0;
	while(str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strrev(char *str)
{
	int i;
	int len;
	char aux;
	
	i = 0;
	len = ft_len(str) - 1;
	while(i < len)
	{
		aux = str[i];
		str[i] = str[len];
		str[len] = aux;
		i++;
		len--;
	}
	return (str);
}