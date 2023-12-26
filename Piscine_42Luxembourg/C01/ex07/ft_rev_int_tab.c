/*
 Funções permitidas: Nenhuma
• Crie uma função que reverta um determinado array de inteiros (o primeiro vai para o último, etc.).
• Os argumentos são um ponteiro para int e o número de inteiros no array.
• Veja como deve ser prototipado:
void ft_rev_int_tab(int *tab, int size);
*/
#include <stdio.h>
#define TAM 9

void ft_rev_int_tab(int *tab, int size);

int main()
{
    int nb[TAM] = {1,2,3,4,5,6,7,8,9};
    int i;

    i = 0;
    ft_rev_int_tab(nb, TAM);
    while(i < TAM)
    {
        printf("%d",nb[i]);
        i++;
    }
    printf("\n");
    return(0);
}

void ft_rev_int_tab(int *tab, int size)
{
    int start;
    int end;
    int temp;

    end = size - 1;
    start = 0;
    while(start <= end)
    {
        temp = tab[start];
        tab[start] = tab[end];
        tab[end] = temp;
        start++;
        end--;
    }

}