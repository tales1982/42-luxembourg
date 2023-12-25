/*
  A função atoi() em C converte uma string para um valor do tipo inteiro. 
  O nome atoi significa "ASCII to integer" (ASCII para inteiro),
  e ela analisa os caracteres de uma string até encontrar o primeiro não numérico,
  retornando o valor inteiro correspondente aos caracteres numéricos encontrados.

 Por exemplo, se você tem a string "123" e usa atoi("123"),
 ela retornará o número inteiro 123.
*/

#include <stdio.h>
#include <unistd.h>

int	ft_atoi(char *str);

int	main(int ac, char **av)
{
	if(ac <= 1)
	{
		printf("ERRO, folta passa os argumentos.\n");
		return (1);
	}	
		
	int	i;
	
	i = 1;
	while(i < ac)
	{
		printf("%d\n",ft_atoi(av[i]));
		i++;
	}
}

int	ft_atoi(char *str)
{
	int	num;
	int	sinal;

	num = 0;
	sinal = 1;
	while (*str == 32 || (*str >= 9 && *str <=13))
	{
		str++;  		
	}
	while (*str == 43 || *str == 45)
	{
		if(*str == 45)
		{
			sinal *= -1;	
		}
		str++;
	}
	while((*str >= 65 && *str <=90)||(*str >= 97 && *str <=122))
	{
		str++;
	}
	while(*str >= 48 && *str <= 57)
	{
		num = (num * 10) + (*str - 48);
		str++;
	}
	
	return (num * sinal);
}


