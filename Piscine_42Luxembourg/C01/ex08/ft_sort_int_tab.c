/*
  Funções permitidas: Nenhuma
• Crie uma função que classifique um array de inteiros em ordem crescente.
• Os argumentos são um ponteiro para int e o número de inteiros no array.
• Veja como deve ser prototipado:
  void ft_sort_int_tab(int *tab, int size);
*/
#include <stdio.h>
#define TAM 9
void ft_sort_int_tab(int *tab, int size);

int main(void)
{
    int nb[TAM] = {2,8,3,9,4,6,7,1,5};
    int i;
    
    ft_sort_int_tab(nb,TAM);

    i = 0;
    while(i < TAM)
    {
        printf("%d",nb[i]);
        i++;
    }
    printf("\n");
    return(0);
}

void ft_swap(int *a, int *b)
{
    int aux;

    aux = *a;
    *a = *b;
    *b = aux;
}

void ft_sort_int_tab(int *tab, int size) {

    int i;
    int ativa_loop;
    
    ativa_loop = 1;
    while(ativa_loop)//enquanto for verdadeiro
    {
        ativa_loop = 0;
        i = 0;
        while (i < size -1)
        {
            if(tab[i] > tab[i + 1])
            {
                ft_swap(&tab[i],&tab[i +1]);
                ativa_loop = 1;
            }
            i++;
        }
        
    }



}