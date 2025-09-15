/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:55:32 by tales             #+#    #+#             */
/*   Updated: 2025/09/11 18:02:24 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
----- Etapa-3 -----
Guardar todas as linhas de um ficheiro em um array de strings usando malloc/calloc.
👉 Treina arrays 2D.
Libertar corretamente toda a memória com free.
👉 Previne memory leaks.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int ac, char **av) {
    if(ac <= 1)
    {
        printf("Error: Insufficient argument.");
        return 1;    
    }
    
    FILE *file = fopen(av[1],"r");
    if(file == NULL)
    {
        perror("File not found");
        return 1;
    }

    char *buffer = NULL;
    size_t linha = 0;
    ssize_t totalCaract = 0;

    char **map = NULL;
    int countLine = 0;

    while ((totalCaract = getline(&buffer, &linha, file))!= -1)
    {

        map = realloc(map,(countLine + 1) * sizeof(char *));
        if(map == NULL)
        {
            perror("Erro realoc");
            free(buffer);
            fclose(file);
            return 1;
        }
        map[countLine] = strdup(buffer);
        countLine++;
    }

    free(buffer);
    fclose(file);
    
    for (size_t i = 0; i < countLine; i++)
    {
        printf("%s",map[i]);
    }
    
    
    return 0;
}
