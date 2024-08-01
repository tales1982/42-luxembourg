/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:07:31 by tlima-de          #+#    #+#             */
/*   Updated: 2024/08/01 12:59:19 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int ft_len(char *str)
{
    int i = 0;
    while (str[i] != '\0')
        i++;
    return i;
}

int ft_char_in_str(char c, char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == c)
            return 1;
        i++;
    }
    return 0;
}

char *ft_union(char *str, char *str2)
{
    int i = 0;
    int k = 0;
    int len = ft_len(str) + ft_len(str2);
    char *aux = (char *)malloc(sizeof(char) * (len + 1));
    
    if (aux == NULL)
        return NULL;

    // Adiciona caracteres únicos de str
    while (str[i] != '\0')
    {
        if (!ft_char_in_str(str[i], aux))
        {
            aux[k] = str[i];
            k++;
        }
        i++;
    }

    i = 0;
    // Adiciona caracteres únicos de str2
    while (str2[i] != '\0')
    {
        if (!ft_char_in_str(str2[i], aux))
        {
            aux[k] = str2[i];
            k++;
        }
        i++;
    }

    aux[k] = '\0';
    return aux;
}

int main(void)
{
    char *str = "rien";
    char *str2 = "cette phrase ne cache rien";
    char *aux;

    aux = ft_union(str, str2);
    printf("%s\n", aux);

    free(aux);
    return 0;
}
