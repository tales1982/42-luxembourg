/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 13:23:50  by tales            #+#    #+#             */
/*   Updated: 2023/12/17 13:38:55  by tales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
  Funções autorizadas : Nenhuma
• Reproduzir de forma idêntica o funcionamento da função strcat (man strcat).
• Ela deverá ser prototipada da seguinte maneira:
  char *ft_strcat(char *dest, char *src);

  A função strcat em C é usada para concatenar (ou unir) duas strings.
  Ela concatena a string de origem (source) à string de destino 
*/

#include <stdio.h>
#include <string.h>

 char *ft_strcat(char *dest, char *src);

 int main()
 {
    char str1[20] = "Tales ";
    char str2[] = "Lima";

    printf("%s\n",str1);
    ft_strcat(str1,str2);
    printf("%s\n",str1);



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

  char *ft_strcat(char *dest, char *src)
  {
    int len;
    int i;

    len = ft_strlen(dest);
    i = 0;
    while(src[i] != '\0')
    {
        dest[len] = src[i];
        len++;
        i++; 
    }
    dest[len] = '\0';
    return(dest);

  }