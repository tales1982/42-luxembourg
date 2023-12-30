/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 13:53:23  by tales            #+#    #+#             */
/*   Updated: 2023/12/17 14:08:15  by tales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
  Funções autorizadas : Nenhuma
• Reproduzir de forma idêntica o funcionamento da função strncat (man strncat).
• Ela deverá ser prototipada da seguinte maneira:
  char *ft_strncat(char *dest, char *src, unsigned int nb);

A função ft_strncat é uma variação da função strcat, porém com um parâmetro 
adicional que determina o número máximo de caracteres a serem concatenados da 
string de origem (src) para a string de destino (dest).
*/
#include <stdio.h>
char *ft_strncat(char *dest, char *src, unsigned int nb);

int main()
{
    char dest[20] = "Tales ";
    char src[] = "Lima";

    printf("%s\n",dest);
    ft_strncat(dest, src, 2);
    printf("%s\n",dest);
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
    return(i);
}

char *ft_strncat(char *dest, char *src, unsigned int nb)
{
    int i;
    int len;

    i = 0;
    len =ft_strlen(dest);
    while(i < nb && src[i] != '\0')
    {
        dest[len] = src[i];
        len++;
        i++;
    }
    dest[len] = '\0';
    return(dest);
}

