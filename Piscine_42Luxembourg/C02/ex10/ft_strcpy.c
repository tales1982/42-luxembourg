/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:34:01  by tales            #+#    #+#             */
/*   Updated: 2023/12/17 12:45:47  by tales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
  Funções autorizadas : Nenhuma
  Reproduzir de forma idêntica o funcionamento da função strlcpy (man strlcpy).
  Ela deverá ser prototipada da seguinte maneira:
  unsigned int ft_strlcpy(char *dest, char *src, unsigned int size);

  strcpy (variável, string); Essa função copia o valor da string na segunda 
  posição do argumento para uma variável string na primeira posição.
*/

#include <stdio.h>

unsigned int ft_strlcpy(char *dest, char *src, unsigned int size);

int main()
{
    int len;
    char src[] = "Tales";
    char dest[] = " ";

    len = ft_strlcpy(dest, src,5);
    printf("%d\n",len);
    printf("%s\n",dest);
    return(0);
}

unsigned int ft_strlcpy(char *dest, char *src, unsigned int size)
{
    int i ;

    i = 0;
    while (i < size - 1 && src[i] !='\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    
    // Retorna o comprimento da string de origem
    while (src[i] != '\0') {
        i++;
    }
    return i;
}