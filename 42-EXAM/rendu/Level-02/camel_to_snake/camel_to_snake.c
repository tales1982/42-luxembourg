/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camel_to_snake.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 20:02:42 by tales             #+#    #+#             */
/*   Updated: 2024/07/23 21:01:49 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


int ft_size(char *str)
{
    int i;

    i = 0;
    while(str[i] != '\0')
        i++;
    return(i);
}
void camel_to_snake(char *str)
{
    int i;
    int j;
    int len;
    char *aux;

    i = 0;
    j = 0;
    len = ft_size(str);
    aux = (char *)malloc(sizeof(char) * (len + 1));
    if(aux == NULL)
        write(1, "ERRO", 4);
    while(str[i] != '\0')
    {
        
        if(str[i] >='A' && str[i] <= 'Z')
        {
            aux[j++] = '_';
            //j++;
            aux[j++] = str[i] + 32;
            //j++;
        }
        else
            aux[j++] = str[i];
        i++;
    }
    aux[j] = '\0'; // Adiciona o caractere nulo ao final da string

    // Imprime a string resultante
    i = 0;
    while (aux[i] != '\0')
    {
        write(1, &aux[i], 1);
        i++;
    }
    write(1, "\n", 1);

    // Libera a memória alocada
    free(aux);
    

    
}


int main()
{
    char *s = "olaMais";
    
    camel_to_snake(s);
}