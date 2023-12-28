/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:10:11  by tales            #+#    #+#             */
/*   Updated: 2023/12/17 12:34:24  by tales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
  Funções autorizadas : Nenhuma
  Escreva uma função que deixe a primeira letra de cada palavra em maiúsculo e o
  resto da palavra em minúsculo.
  Uma palavra é uma sequência de caracteres alfanuméricos.
  Ela deverá ser prototipada da seguinte maneira:
  char *ft_strcapitalize(char *str);
  Ela deverá retornar str.
  Por exemplo:
•  oi, tudo bem? 42palavras quarenta-e-duas; cinquenta+e+um
  Deve resultar:
• Oi, Tudo Bem? 42palavras Quarenta-E-Duas; Cinquenta+E+Um
*/

#include <stdio.h>

char *ft_strcapitalize(char *str);

int main() {
    char str[] = "oi, tudo bem? 42palavras quArenta-e-duas; cinquenta+e+um";
    char *res;

    res = ft_strcapitalize(str);

    printf("%s\n", res);
    return 0;
}

char *ft_strcapitalize(char *str) {
    int i = 0;

    while (str[i] != '\0') {
        // Converte a primeira letra de cada palavra para maiúscula
        if ((str[i] >= 'a' && str[i] <= 'z') && (i == 0 || (str[i - 1] < '0' || (str[i - 1] > '9' && str[i - 1] < 'A') || (str[i - 1] > 'Z' && str[i - 1] < 'a') || str[i - 1] > 'z'))) {
            str[i] -= 32;
        } else if ((str[i] >= 'A' && str[i] <= 'Z') && (i != 0 && ((str[i - 1] >= '0' && str[i - 1] <= '9') || (str[i - 1] >= 'A' && str[i - 1] <= 'Z') || (str[i - 1] >= 'a' && str[i - 1] <= 'z')))) {
            // Converte letras maiúsculas para minúsculas após a primeira letra da palavra
            str[i] += 32;
        }
        i++;
    }
    return str;
}
