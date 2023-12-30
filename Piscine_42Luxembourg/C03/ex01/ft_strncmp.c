/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 13:01:10  by tales            #+#    #+#             */
/*   Updated: 2023/12/17 13:16:25  by tales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*Funções autorizadas : Nenhuma
•Reproduzir de forma idêntica o funcionamento da função strncmp (man strncmp).
•Ela deverá ser prototipada da seguinte maneira:
int ft_strncmp(char *s1, char *s2, unsigned int n);


A função strncmp é uma função da linguagem C presente na biblioteca padrão <string.h>. 
Ela é usada para comparar os primeiros n caracteres de duas strings.
Ela compara os primeiros n caracteres das strings str1 e str2, 
retornando um valor inteiro que indica a relação entre esses trechos das strings:
*/
#include <string.h>
#include <stdio.h>
int ft_strncmp(char *s1, char *s2, unsigned int n);

int main() {
    const char str1[] = "Hell";
    const char str2[] = "Hell";
    int result = strncmp(str1, str2, 5);
    int result2 = strncmp(str1, str2, 5);

    if (result < 0) {
        printf("Os primeiros 4 caracteres de str1 são menores que os de str2.\n");
    } else if (result == 0) {
        printf("Os primeiros 4 caracteres de str1 são iguais aos de str2.\n");
    } else {
        printf("Os primeiros 4 caracteres de str1 são maiores que os de str2.\n");
    }

  
    printf("AUX1..: %d\n",result);
    printf("AUX2..: %d\n",result2);

    return 0;
}

int ft_strncmp(char *s1, char *s2, unsigned int n)
{
unsigned int i = 0;

    while (i < n && *s1 && *s2 && *s1 == *s2) {
        s1++;
        s2++;
        i++;
    }

    if (i == n) {
        return 0; // Se chegarmos ao final de n caracteres, são iguais
    } else {
        return ((unsigned char)*s1 - (unsigned char)*s2); // Retorna a diferença lexicográfica
    }
}


