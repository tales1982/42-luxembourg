/*
Funções permitidas: Nenhuma
• Crie uma função ft_ultimate_div_mod com o seguinte protótipo:
void ft_ultimate_div_mod(int *a, int *b);
• Esta função divide os parâmetros a por b. O resultado desta divisão é armazenado no
int apontado por a. O restante da divisão é armazenado no int apontado por b.
*/

#include <stdio.h>

void ft_ultimate_div_mod(int *a, int *b);

int main()
{
    int a;
    int b;

    a = 10;
    b = 2;

    ft_ultimate_div_mod(&a, &b);
    printf("%d\n",a);
    printf("%d\n",b);
    return(0);
}

void ft_ultimate_div_mod(int *a, int *b)
{
    int temp;

    temp = *a;

    *a = temp / *b;
    *b = temp % *b;
}