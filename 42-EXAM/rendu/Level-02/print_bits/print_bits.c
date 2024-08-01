/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 19:24:19 by tales             #+#    #+#             */
/*   Updated: 2024/07/31 19:50:43 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void print_bits(unsigned char octet) {
    int i = 7;

    while (i >= 0) {
        if (octet & (1 << i))
            write(1, "1", 1);
        else
            write(1, "0", 1);
        i--;
    }
}

int main() {
    unsigned char octet = 2; // Exemplo com o caractere 'A' que é 65 em ASCII
    print_bits(octet); // Deve imprimir 01000001 para o caractere 'A'
    write(1, "\n", 1);
    return 0;
}
