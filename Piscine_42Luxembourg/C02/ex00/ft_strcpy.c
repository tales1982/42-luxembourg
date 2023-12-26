/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 8:11:11 by tales             #+#    #+#             */
/*   Updated: 2023/12/17 8:38:33 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
  Funções autorizadas : Nenhuma
  Reproduzir de forma idêntica o funcionamento da função strcpy (man strcpy).
  Ela deverá ser prototipada da seguinte maneira:
  char *ft_strcpy(char *dest, char *src);
 
  • A função strcpy() copia a string-origem para a string- destino. 
*/
#include <stdio.h>
char *ft_strcpy(char *dest, char *src);

int main()
{
    char str[] = "TALES";
    char dest[] = "";

    printf("ORIGINAL..: %s\n",str);
    ft_strcpy(dest, str);
    printf("COPIA..: %s\n",dest);

    return(0);
}

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while(str[i] != '\0')
    {
        i++;
    }
    return (i);
}

char *ft_strcpy(char *dest, char *src)
{
    int i;
    int size;

    size = ft_strlen(src); 
    i = 0;
    while(i < size)
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return(dest);

}
