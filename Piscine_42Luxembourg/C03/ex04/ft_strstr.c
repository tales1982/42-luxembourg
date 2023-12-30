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
    int i;
    int j;

    j = 0; // Inicializa o índice para a substring a procurar
    i = 0; // Inicializa o índice para percorrer a string principal

    // Se a substring a procurar é vazia, retorna a string original
    if (to_find[j] == '\0')
        return (str);

    // Enquanto não chegarmos ao fim da string principal
    while (str[i] != '\0')
    {
        // Enquanto os caracteres coincidirem e não chegarmos ao fim da substring
        while (str[i + j] == to_find[j] && str[i + j] != '\0')
            j++; // Avança nos índices para comparar os próximos caracteres

        // Se chegamos ao fim da substring, retorna a posição atual da string principal
        if (to_find[j] == '\0')
            return (str + i);

        // Se não, avança para o próximo caractere na string principal
        i++;
        j = 0; // Reinicia o índice da substring para a próxima iteração
    }

    // Se a substring não foi encontrada, retorna NULL
    return (0);
}


#include<stdio.h>
int	main(void)
{
	char *str = "hoje vou joga futbol no campo";
	char *find = "no";

	printf("%s\n", ft_strstr(str, find));
	return (0);
}
