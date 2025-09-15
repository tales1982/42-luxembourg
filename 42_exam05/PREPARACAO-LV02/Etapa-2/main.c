/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 09:21:59 by tales             #+#    #+#             */
/*   Updated: 2025/09/10 16:16:34 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
----- Etapa-2 -----
Remover o \n do fim da string lida por getline.
👉 Treina índices e strlen.
Verificar se todas as linhas de um ficheiro têm o mesmo comprimento.
👉 É o início da validação do mapa.
Verificar se uma linha só contém caracteres de um conjunto válido
(por exemplo, apenas "0 ..").
👉 Treina loops e comparação de caracteres.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int ac, char **av)
{
    if (ac <= 1)
    {
        printf("Error: Insufficient argument\n");
        return 1;
    }

    FILE *file = fopen(av[1], "r");
    if (!file)
    {
        printf("File not found\n");
        return 1;
    }

    char *buffer = NULL;
    size_t cap = 0;
    ssize_t n;
    int isValidLine;
    int linhaN = 0;

    while ((n = getline(&buffer, &cap, file)) != -1)
    {
        if (n > 0 && buffer[n - 1] == '\n')
            buffer[--n] = '\0';

        isValidLine = 1; // valido

        if (n == 0)
            isValidLine = 0;
        else
        {   
            for (int i = 0; i < n; i++)
            {
                char c = buffer[i];
                if (c != '.' && c != 'o')
                {
                    printf("___________________________________\n");
                    printf("|\n");
                    printf("|   Error: Invalid char '%c'\n|   Error na linha %d\n|   Coluna %d\n", c, linhaN + 1, i + 1);
                    printf("|__________________________________\n");
                    isValidLine = 0;
                }
            }
            if (isValidLine != 1)
                printf("\n### Mapa NAO e valido ###\n");
        }
        linhaN++;

        // Debug útil
        // printf("len=%zd valid=%d |%s|\n", n, isValidLine, buffer);
    }

    free(buffer);
    fclose(file);
    return 0;
}
