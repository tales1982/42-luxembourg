/*
 * Ficheiros para entregar : ft_range.c
Funções autorizadas : malloc
• Escreva uma função ft_range que inverta um array de int. Esse array de int
deverá conter todos os valores entre min e max.
• Min incluído - max excluído.
• Ela deverá ser prototipada da seguinte maneira:
int *ft_range(int min, int max);
• Se o valor min for superior ou igual ao valor max, um ponteiro nulo será retornado
*/
#include <stdlib.h>
#include <stdio.h>

int	*ft_range(int min, int max);

int	main()
{
	int	min;
	int	max;
	int	i;

	i = 0;
	min = -25;
	max = 10;
	int *mat;

	mat = ft_range(min, max);
	while (i < max - min)
	{
		printf("%d,", mat[i]);
		i++;
	}
	free(mat);
	return (0);
}


int	*ft_range(int min, int max)
{
	int	i;
	int	size;
	int	*res;
	
	size = max - min;
	if (min >= max)
		return (NULL);
	res = (int *)malloc(size * sizeof(int));
	if(res == NULL)
	{
		printf("ERRO alocacao de memoria.");
		return (NULL);
	}
	i = 0;
	while(min < max)
	{
		
		res[i] = min;
		min++;
		i++;
	}
	return (res);
  
}








