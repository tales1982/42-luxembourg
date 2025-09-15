// bsq.c
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/* =========================
   Utilitários sem libc extra
   ========================= */

static int my_is_printable(char c) {
    return (c >= 32 && c <= 126);
}


static char *my_strndup(const char *s, size_t n) {
    char *p = (char *)malloc(n + 1);
    if (!p) return NULL;
    for (size_t i = 0; i < n; i++) p[i] = s[i];
    p[n] = '\0';
    return p;
}

static int my_min3(int a, int b, int c) {
    int m = a < b ? a : b;
    return (m < c ? m : c);
}

/* ==============
   Estruturas
   ============== */

typedef struct {
    int linhas;
    int colunas;
    char empty;
    char obstacle;
    char full;
    char **lines; /* linhas de texto, sem '\n' no final */
} Map;

/* =========================
   Leitura e validação
   ========================= */

static void free_map(Map *map) {
    if (!map) return;
    if (map->lines) {
        for (int i = 0; i < map->linhas; i++) {
            free(map->lines[i]);
        }
        free(map->lines);
    }
    map->lines = NULL;
}

static int ler_cabecalho(FILE *f, Map *map) {
    /* Lê: <linhas> <empty> <obstacle> <full> (separados por espaço) */
    if (fscanf(f, "%d %c %c %c\n",
               &map->linhas, &map->empty, &map->obstacle, &map->full) != 4) {
        return 0;
    }
    if (map->linhas < 1) return 0;
    /* Chars devem ser imprimíveis e distintos */
    if (!my_is_printable(map->empty) ||
        !my_is_printable(map->obstacle) ||
        !my_is_printable(map->full)) {
        return 0;
    }
    if (map->empty == map->obstacle ||
        map->empty == map->full ||
        map->obstacle == map->full) {
        return 0;
    }
    return 1;
}

static int ler_mapa(FILE *f, Map *map) {
    char *buf = NULL;
    size_t cap = 0;
    ssize_t got;
    int expected_cols = -1;

    map->colunas = 0;
    map->lines = (char **)calloc((size_t)map->linhas, sizeof(char *));
    if (!map->lines) {
        free(buf);
        return 0;
    }

    for (int i = 0; i < map->linhas; i++) {
        got = getline(&buf, &cap, f);
        if (got < 0) { /* não conseguiu ler linha suficiente */
            free(buf);
            return 0;
        }
        if (got == 0) { /* linha vazia inesperada */
            free(buf);
            return 0;
        }
        /* Cada linha deve terminar com '\n' */
        if (buf[got - 1] != '\n') {
            free(buf);
            return 0;
        }
        /* Tira o '\n' para processar e guardar */
        size_t len = (size_t)got - 1;
        if (expected_cols == -1)
            expected_cols = (int)len;
        else if (expected_cols != (int)len) {
            free(buf);
            return 0; /* todas as linhas devem ter mesmo comprimento */
        }
        if (len == 0) { /* pelo menos 1 coluna */
            free(buf);
            return 0;
        }

        /* Valida caracteres: só empty ou obstacle */
        for (size_t j = 0; j < len; j++) {
            char c = buf[j];
            if (!(c == map->empty || c == map->obstacle)) {
                free(buf);
                return 0;
            }
        }

        /* Guarda linha sem '\n' */
        map->lines[i] = my_strndup(buf, len);
        if (!map->lines[i]) {
            free(buf);
            return 0;
        }
    }

    map->colunas = expected_cols;
    free(buf);
    return 1;
}

/* =========================
   Resolução por DP
   ========================= */

typedef struct {
    int top, left, size;
} Square;

static void resolver_bsq(Map *map, Square *best) {
    int L = map->linhas;
    int C = map->colunas;

    best->size = 0;
    best->top = 0;
    best->left = 0;

    if (L <= 0 || C <= 0) return;

    /* DP com duas linhas para economizar memória */
    int *prev = (int *)calloc((size_t)C, sizeof(int));
    int *curr = (int *)calloc((size_t)C, sizeof(int));
    if (!prev || !curr) {
        free(prev); free(curr);
        return;
    }

    for (int i = 0; i < L; i++) {
        for (int j = 0; j < C; j++) {
            if (map->lines[i][j] == map->obstacle) {
                curr[j] = 0;
            } else {
                if (i == 0 || j == 0) {
                    curr[j] = 1;
                } else {
                    int a = prev[j];     /* cima */
                    int b = curr[j - 1]; /* esquerda */
                    int c = prev[j - 1]; /* diagonal sup-esq */
                    curr[j] = 1 + my_min3(a, b, c);
                }
                /* Atualiza melhor (desempate: mais alto, depois mais à esquerda) */
                int size = curr[j];
                if (size > 0) {
                    int top = i - size + 1;
                    int left = j - size + 1;
                    if (size > best->size ||
                        (size == best->size && top < best->top) ||
                        (size == best->size && top == best->top && left < best->left)) {
                        best->size = size;
                        best->top = top;
                        best->left = left;
                    }
                }
            }
        }
        /* swap prev/curr e zera curr */
        int *tmp = prev; prev = curr; curr = tmp;
        for (int j = 0; j < C; j++) curr[j] = 0;
    }

    free(prev);
    free(curr);
}

/* =========================
   Aplicação e impressão
   ========================= */

static void aplicar_solucao(Map *map, const Square *best) {
    if (best->size <= 0) return; /* nada a marcar */
    int r2 = best->top + best->size;
    int c2 = best->left + best->size;
    for (int r = best->top; r < r2; r++) {
        for (int c = best->left; c < c2; c++) {
            map->lines[r][c] = map->full;
        }
    }
}

static void imprimir_mapa(const Map *map) {
    for (int i = 0; i < map->linhas; i++) {
        /* imprime a linha e um '\n' */
        fputs(map->lines[i], stdout);
        fputs("\n", stdout);
    }
}

/* =========================
   Pipeline por stream
   ========================= */

static int processar_stream(FILE *f) {
    Map map;
    map.linhas = 0;
    map.colunas = 0;
    map.empty = '.';
    map.obstacle = 'o';
    map.full = 'x';
    map.lines = NULL;

    if (!ler_cabecalho(f, &map)) {
        fprintf(stderr, "map error\n");
        return 0;
    }
    if (!ler_mapa(f, &map)) {
        free_map(&map);
        fprintf(stderr, "map error\n");
        return 0;
    }

    Square best;
    resolver_bsq(&map, &best);
    aplicar_solucao(&map, &best);
    imprimir_mapa(&map);
    /* cada solução deve ser seguida por uma quebra de linha */
    fputs("\n", stdout);

    free_map(&map);
    return 1;
}

/* =========================
   main
   ========================= */

int main(int argc, char **argv) {
    if (argc == 1) {
        /* Lê um único mapa da stdin */
        processar_stream(stdin);
        return 0;
    }

    for (int i = 1; i < argc; i++) {
        FILE *f = fopen(argv[i], "r");
        if (!f) {
            /* Se nem abrir o arquivo, é um erro de mapa para este item */
            fprintf(stderr, "map error\n");
            /* mesmo assim, seguir para o próximo */
            continue;
        }
        processar_stream(f);
        fclose(f);
    }
    return 0;
}
