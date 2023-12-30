/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:23:23  by tales            #+#    #+#             */
/*   Updated: 2023/12/17 14:38:15  by tales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
  Funções autorizadas : Nenhuma
• Reproduzir de forma idêntica o funcionamento da função strstr (man strstr).
• Ela deverá ser prototipada da seguinte maneira:
  char *ft_strstr(char *str, char *to_find);

A função strstr em C é utilizada para encontrar a primeira 
ocorrência de uma substring dentro de outra string maior. 
Ela retorna um ponteiro para o primeiro caractere da primeira ocorrência da 
substring na string maior ou retorna NULL se a substring não for encontrada.
*/

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (to_find[j] == '\0')
		return (str);
	while (str[i] != '\0')
	{
		while (str[i + j] == to_find[j] && str[i + j] != '\0')
			j++;
		if (to_find[j] == '\0')
			return (str + i);
		i++;
		j = 0;
	}
	return (0);
}

#include<stdio.h>
int	main(void)
{
	char *str = "hoje vou joga futbol no campo";
	char *find = "futbol";

	printf("%s\n", ft_strstr(str, find));
	return (0);
}
