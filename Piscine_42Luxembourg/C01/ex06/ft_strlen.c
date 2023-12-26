/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 15:30:19 by tales             #+#    #+#             */
/*   Updated: 2023/12/16 15:58:01 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
Funções permitidas: Nenhuma
• Crie uma função que conte e retorne o número de caracteres em uma string.
• Veja como deve ser prototipado:
int ft_strlen(char*str);
*/
#include <stdio.h>

int ft_strlen(char*str);

int main()
{
    char n[] = "Ola mundo!";//10
    printf("Tamanho da string..: %d\n",ft_strlen(n));
    return(0);
}

int ft_strlen(char*str)
{
    int i;

    i = 0;
    while(str [i] != '\0')
    {
        i++;
    }
    return(i);
}