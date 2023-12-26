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