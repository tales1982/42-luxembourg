/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:36:19 by tales             #+#    #+#             */
/*   Updated: 2024/07/31 18:11:48 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*last_word(char *str)
{
	int		i;
	int		size;
	char	*aux;

	i = 0;
	size = ft_len(str) - 1;
	aux = (char *)malloc(sizeof(char) * (ft_len(str) + 1));
	if (aux == NULL)
		return (NULL);
	while (str[size] == ' ')
		size--;
	while (str[size] != ' ')
	{
		aux[i] = str[size];
		size--;
		i++;
	}
	aux[i] = '\0';
	return (aux);
}

void	reverse(char *str)
{
	int		i;
	int		j;
	char	aux;

	i = 0;
	j = ft_len(str) - 1;
	while (j > i)
	{
		aux = str[j];
		str[j] = str[i];
		str[i] = aux;
		i++;
		j--;
	}
}
int	main(int ac, char **av)
{
	char	*aux;

	if (ac == 2)
	{
		aux = last_word(av[1]);
		reverse(aux); // Inverte a string
		printf("%s\n", aux);
		free(aux); // Liberar a memória alocada
	}
	else
		printf("\n");
	return (0);
}
