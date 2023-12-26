/*
Funções permitidas: Nenhuma
• Crie uma função ft_div_mod prototipada assim:
void ft_div_mod(int a, int b, int *div, int *mod);
• Esta função divide os parâmetros a por b e armazena o resultado no int apontado por
div. Também armazena o restante da divisão de a por b no int apontado por mod
*/

#include <stdio.h>
void ft_div_mod(int a, int b, int *div, int *mod);

int main()
{
    int a;
    int b;
    int div;
    int mod;

    a = 33;
    b = 2;
    div = 0;
    mod = 0;
    ft_div_mod(a,b,&div,&mod);
    printf("Div = %d\n",div);
    printf("Resto = %d\n",mod);
}

void ft_div_mod(int a, int b, int *div, int *mod)
{
    *div = a / b;
    *mod = a % b;
}