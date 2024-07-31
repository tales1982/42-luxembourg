/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:49:51 by tales             #+#    #+#             */
/*   Updated: 2024/07/28 16:03:32 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include <stdio.h>

int ft_strlen(char *s)
{
    int i;

    i = 0;
    while(s[i] != '\0')
        i++;
    return(i);
}

char    *ft_strdup(char *src)
{
       int i;
       char *aux;
       
       aux = (char *)malloc(sizeof(char) * ft_strlen(src) + 1);
       if(aux == NULL)
            return(NULL);
       i = 0;
       while(src[i] != '\0')
       {
            aux[i] = src[i];
            i++;
       }
       aux[i] = '\0';
       free(aux);
       return(aux);
}
int main(void)
{
	printf("%s\n", ft_strdup("This is a test!"));
}