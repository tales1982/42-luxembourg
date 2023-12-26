/*
 Funções permitidas: write
• Crie uma função que exiba uma sequência de caracteres na saída padrão.
• Veja como deve ser prototipado:
void ft_putstr(char*str);
*/

#include <unistd.h>

void ft_putstr(char*str);

int main()
{
    char n[] = "Tales";
    ft_putstr(n);

    return(0);
}

void ft_putstr(char*str)
{
    int i;

    i = 0;
    while(str[i] != '\0')
    {
        write(1, &str[i], 1);
        i++;
    }
    write(1, "\n", 1);
}