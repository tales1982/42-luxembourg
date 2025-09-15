/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 08:55:34 by tales             #+#    #+#             */
/*   Updated: 2025/09/10 16:16:20 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
----- Etapa-1 -----
Ler uma linha do stdin com getline e imprimir no ecrã.
👉 Treina getline.
Abrir um ficheiro com fopen e ler todas as linhas até EOF.
👉 Treina fopen, fclose.
Contar o número de linhas num ficheiro.
👉 Treina laços (while (getline...)).
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int ac, char **av)
{
    if(ac <= 1)
    {
        printf("Error: Insufficient argument");
        return 1;
    }

    FILE *file = fopen(av[1], "r");
    if(file == NULL)
    {
        perror("Error: File not found.");
        fclose(file);
        return 1;
    }

    char *buffer = NULL;
    size_t linha = 0;
    ssize_t numeroCaracteres = 0;

    while ((numeroCaracteres = getline(&buffer,&linha,file)) != -1)
    {
        printf("%s",buffer);
    }

    free(buffer);
    fclose(file);
    return 0;
    
}