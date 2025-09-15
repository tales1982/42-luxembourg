/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:06:57 by tales             #+#    #+#             */
/*   Updated: 2025/09/11 20:43:40 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
----- Etapa-4 -----
Criar uma struct Map com:
número de linhas (h),
número de colunas (w),
char empty, char obstacle, char full,
char **lines.
👉 Já começa a parecer com o BSQ.
Ler o cabeçalho (n empty obstacle full) com fscanf.
👉 Treina parsing.
Validar se os 3 caracteres são distintos.
👉 Parte da regra de mapa válido.
<h2> Etapa 5 — Algoritmo do maior quadrado (DP) 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int linhas;
    int colunas;
    char empty;
    char obstacle;
    char full;
    char **lines;
} Map;

/* ---------- Funções utilitárias ---------- */

// Lê o cabeçalho do mapa
int ler_cabecalho(FILE *f, Map *map) {
    if (fscanf(f, "%d %c %c %c\n", &map->linhas,
               &map->empty, &map->obstacle, &map->full) != 4) {
        return 0; // erro de parsing
    }
    return 1;
}

// Lê as linhas do mapa para map->lines
int ler_linhas(FILE *f, Map *map) {
    map->lines = malloc(sizeof(char *) * map->linhas);
    if (!map->lines) return 0;

    char buffer[1024];
    for (int i = 0; i < map->linhas; i++) {
        if (!fgets(buffer, sizeof(buffer), f))
            return 0;

        buffer[strcspn(buffer, "\n")] = '\0'; // tira o \n
        if (i == 0)
            map->colunas = strlen(buffer);

        if ((int)strlen(buffer) != map->colunas)
            return 0; // linhas de tamanhos diferentes

        map->lines[i] = strdup(buffer);
    }
    return 1;
}

// Libera memória do mapa
void liberar(Map *map) {
    for (int i = 0; i < map->linhas; i++)
        free(map->lines[i]);
    free(map->lines);
}

/* ---------- Algoritmo DP ---------- */

// Encontra maior quadrado vazio
void encontrar_quadrado(Map *map) {
    int **dp = malloc(map->linhas * sizeof(int *));
    for (int i = 0; i < map->linhas; i++) {
        dp[i] = calloc(map->colunas, sizeof(int));
    }

    int maxSize = 0, maxRow = 0, maxCol = 0;

    for (int i = 0; i < map->linhas; i++) {
        for (int j = 0; j < map->colunas; j++) {
            if (map->lines[i][j] == map->empty) {
                if (i == 0 || j == 0)
                    dp[i][j] = 1;
                else {
                    int min = dp[i-1][j];
                    if (dp[i][j-1] < min) min = dp[i][j-1];
                    if (dp[i-1][j-1] < min) min = dp[i-1][j-1];
                    dp[i][j] = 1 + min;
                }
                if (dp[i][j] > maxSize) {
                    maxSize = dp[i][j];
                    maxRow = i;
                    maxCol = j;
                }
            }
        }
    }

    // Preenche quadrado com `full`
    for (int i = maxRow; i > maxRow - maxSize; i--) {
        for (int j = maxCol; j > maxCol - maxSize; j--) {
            map->lines[i][j] = map->full;
        }
    }

    // Libera memória dp
    for (int i = 0; i < map->linhas; i++)
        free(dp[i]);
    free(dp);
}

/* ---------- Programa principal ---------- */

int main(int ac, char **av) {
    if (ac < 2) {
        fprintf(stderr, "Uso: %s arquivo_mapa\n", av[0]);
        return 1;
    }

    FILE *f = fopen(av[1], "r");
    if (!f) {
        perror("Erro ao abrir arquivo");
        return 1;
    }

    Map map;
    if (!ler_cabecalho(f, &map)) {
        fprintf(stderr, "map error\n");
        fclose(f);
        return 1;
    }

    if (!ler_linhas(f, &map)) {
        fprintf(stderr, "map error\n");
        fclose(f);
        return 1;
    }
    fclose(f);

    encontrar_quadrado(&map);

    // imprime resultado
    for (int i = 0; i < map.linhas; i++)
        puts(map.lines[i]);

    liberar(&map);
    return 0;
}
