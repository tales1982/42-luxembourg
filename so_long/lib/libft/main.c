#include"libft.h"

int main(void) {
    // Teste 1: Alocação de um array de 5 inteiros
    int *arr1 = (int *)ft_calloc(5, sizeof(int));
    if (arr1 != NULL) {
        printf("Teste 1: Array de inteiros alocado com sucesso.\n");
        free(arr1);  // Liberar a memória alocada
    } else {
        printf("Teste 1: Falha na alocação do array de inteiros.\n");
    }

    // Teste 2: Alocação de um array de 10 doubles
    double *arr2 = (double *)ft_calloc(10, sizeof(double));
    if (arr2 != NULL) {
        printf("Teste 2: Array de doubles alocado com sucesso.\n");
        free(arr2);  // Liberar a memória alocada
    } else {
        printf("Teste 2: Falha na alocação do array de doubles.\n");
    }

    // Teste 3: Tentativa de alocação de um array muito grande para forçar falha
    char *arr3 = (char *)ft_calloc(1000000000, sizeof(char));
    if (arr3 != NULL) {
        printf("Teste 3: Array alocado com sucesso (o teste pode estar incorreto).\n");
        free(arr3);  // Liberar a memória alocada
    } else {
        printf("Teste 3: Falha na alocação (como esperado para um array muito grande).\n");
    }

    return 0;
}

