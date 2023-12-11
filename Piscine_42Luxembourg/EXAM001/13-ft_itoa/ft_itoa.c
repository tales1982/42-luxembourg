#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* reverse_string(char* str) {
    int length = strlen(str);
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
    return str;
}

char* itoa(int num, char* buffer) {
    int i = 0;
    int isNegative = 0;

    // Caso o número seja negativo
    if (num < 0) {
        isNegative = 1;
        num = -num;
    }

    // Caso especial para 0
    if (num == 0) {
        buffer[i++] = '0';
    } else {
        // Convertendo cada dígito para caracteres e armazenando no buffer
        while (num != 0) {
            int rem = num % 10;
            buffer[i++] = rem + '0';
            num = num / 10;
        }
    }

    // Se for negativo, adiciona o sinal '-' no buffer
    if (isNegative) {
        buffer[i++] = '-';
    }

    buffer[i] = '\0'; // Adicionando o caractere nulo para indicar o fim da string
    reverse_string(buffer); // Reverte a string para obter o número correto

    return buffer;
}

int main() {
    int number = -12345;
    char str[20]; // Alocando espaço para a string

    // Chamando a função itoa para converter o número em uma string
    char* converted = itoa(number, str);

    // Imprimindo o resultado
    printf("O número convertido para string é: %s\n", converted);

    return 0;
}

