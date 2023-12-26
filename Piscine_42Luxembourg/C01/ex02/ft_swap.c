/*
Funções permitidas: Nenhuma
• Crie uma função que troque o valor de dois números inteiros cujos endereços são inseridos
como parâmetros.
• Veja como deve ser prototipado:

void ft_swap(int *a, int *b);
*/

#include <stdio.h>

void ft_swap(int *a, int *b);

int main()
{
    int a;
    int b;

    a = 10;
    b = 30;

    printf("Antes A..: %d\n",a);
    printf("Antes B..: %d\n",b);
    ft_swap(&a,&b);
   printf("========== TROCA ==========\n");
    printf("Depois A..: %d\n",a);
    printf("Depois B..: %d\n",b);
}

void ft_swap(int *a, int *b)
{
    int aux;

    aux = *a;
    *a = *b;
    *b = aux;
}
