/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snake_to_camel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 19:53:55 by tales             #+#    #+#             */
/*   Updated: 2024/07/31 21:50:07 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	ft_size(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*snack_to_camel(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*aux;

	i = 0;
	j = 0;
	len = ft_size(str);
	aux = (char *)malloc(sizeof(char) * (len + 1));
	if (aux == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == '_')
		{
			i++;
			aux[j] = str[i] - 32;
		}
		else
			aux[j] = str[i];
		j++;
		i++;
	}
	aux[j] = '\0';
	return (aux);
}

int	main(void)
{
	char *str = "ola_teste";
	char *aux;

	aux = snack_to_camel(str);
	if (aux != NULL)
	{
		printf("%s\n", aux);
		free(aux);
	}
	else
	{
		printf("Erro de alocação de memória\n");
	}
	return (0);
}