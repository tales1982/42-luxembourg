/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 9:01:27 by tales              #+#    #+#             */
/*   Updated: 2023/12/17 9:28:31 by tales             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
  Funções autorizadas : Nenhuma
  Reproduzir de forma idêntica o funcionamento da função strncpy (man strncpy).
  Ela deverá ser prototipada da seguinte maneira:
  char *ft_strncpy(char *dest, char *src, unsigned int n);

  • A função strncpy é semelhante à função strcpy, porém com uma funcionalidade adicional de copiar 
  apenas um número especificado de caracteres de uma string de origem para uma string de destino.
*/
#include <stdio.h>

char *ft_strncpy(char *dest, char *src, unsigned int n);

int main()
{
    char str[] = "TAL";
    char dest[] = "";

    printf("ORIGINAL..: %s\n",str);
    ft_strncpy(dest, str,5);
    printf("COPIA...: %s\n",dest);
    return(0);
}

char *ft_strncpy(char *dest, char *src, unsigned int n)
{
    int i;

    i = 0;
    while(i < n && src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    // Preenche o restante da string de destino com '\0' se necessário
    while (i < n) {
        dest[i] = '\0';
        i++;
    }
    return (dest);
}