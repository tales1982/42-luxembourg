/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_non_printable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:54:09  by tales            #+#    #+#             */
/*   Updated: 2023/12/17 13:22:17  by tales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
 Funções autorizadas : write
 Escreva uma função que mostre uma string de caracteres na tela. Se essa string
 contiver caracteres não imprimíveis, eles devem ser mostrados na forma hexadecimal
 (em minúsculo) precedidos por um "backslash".
 Por exemplo, com este parâmetro:
 Oi\nvoce esta bem?
 A função deverá mostrar:
 Oi\0avoce esta bem?
 Ela deverá ser prototipada da seguinte maneira:
 void ft_putstr_non_printable(char *str);
*/
/*
#include <unistd.h>
void ft_putstr_non_printable(char *str);

int main()
{

    return(0);
}

void ft_putstr_non_printable(char *str)
{

}
*/
#include <stdio.h>
#include <unistd.h>

//Imprimir em hexadeciaml
/*
void print_hex_char(unsigned char c) {
    char hex[] = "0123456789abcdef";
    write(1, &hex[c / 16], 1);
    write(1, &hex[c % 16], 1);
}

*/

