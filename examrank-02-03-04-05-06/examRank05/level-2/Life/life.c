#include "life.h"

/* ---------- helpers ---------- */

static int  count_neighbors(const t_game *g, int r, int c)
{
    int dr, dc, rr, cc, count;

    count = 0;
    for (dr = -1; dr <= 1; dr++)
    {
        for (dc = -1; dc <= 1; dc++)
        {
            if (dr == 0 && dc == 0) continue;
            rr = r + dr;
            cc = c + dc;
            if (rr >= 0 && rr < g->height && cc >= 0 && cc < g->width)
                if (g->board[rr][cc] == g->alive)
                    count++;
        }
    }
    return count;
}

/* ---------- memory ---------- */

void free_board(t_game *g)
{
    int r;

    if (!g) return;
    if (g->board)
    {
        for (r = 0; r < g->height; r++)
            if (g->board[r]) free(g->board[r]);
        free(g->board);
    }
    g->board = NULL;
}

int init_game(t_game *g, char *argv[])
{
    int r, c;

    g->width      = atoi(argv[1]);
    g->height     = atoi(argv[2]);
    g->iterations = atoi(argv[3]);
    g->alive = '0';
    g->dead  = ' ';
    g->i = 0;
    g->j = 0;
    g->draw = 0;
    g->board = NULL;

    /* validação básica */
    if (g->width <= 0 || g->height <= 0 || g->iterations < 0)
        return -1;

    /* aloca vetor de linhas */
    g->board = (char**)malloc((size_t)g->height * sizeof(char*));
    if (!g->board) return -1;

    /* zera ponteiros para free seguro em falha parcial */
    for (r = 0; r < g->height; r++)
        g->board[r] = NULL;

    /* aloca cada linha com calloc (preenchida com zeros) e seta como ' ' */
    for (r = 0; r < g->height; r++)
    {
        g->board[r] = (char*)malloc((size_t)g->width * sizeof(char));
        if (!g->board[r])
        {
            free_board(g);
            return -1;
        }
        for (c = 0; c < g->width; c++)
            g->board[r][c] = g->dead;
    }
    return 0;
}

/* ---------- input drawing ---------- */

void fill_board(t_game *g)
{
    char ch;

    while (read(STDIN_FILENO, &ch, 1) == 1)
    {
        int valid_cmd = 1; /* reseta a cada byte */

        switch (ch)
        {
            case 'w': if (g->i > 0)                g->i--;                break;
            case 's': if (g->i < g->height - 1)    g->i++;                break;
            case 'a': if (g->j > 0)                g->j--;                break;
            case 'd': if (g->j < g->width  - 1)    g->j++;                break;
            case 'x': g->draw = !g->draw;                                 break;
            default:  valid_cmd = 0;                                      break;
        }
        if (g->draw && valid_cmd)
            g->board[g->i][g->j] = g->alive;
    }
}

/* ---------- game of life step ---------- */

int step_game(t_game *g)
{
    char **next;
    int    r, c;

    next = (char**)malloc((size_t)g->height * sizeof(char*));
    if (!next) return -1;

    for (r = 0; r < g->height; r++)
    {
        next[r] = (char*)malloc((size_t)g->width * sizeof(char));
        if (!next[r])
        {
            int k;
            for (k = 0; k < r; k++) free(next[k]);
            free(next);
            return -1;
        }
    }

    for (r = 0; r < g->height; r++)
    {
        for (c = 0; c < g->width; c++)
        {
            int n = count_neighbors(g, r, c);
            if (g->board[r][c] == g->alive)
                next[r][c] = (n == 2 || n == 3) ? g->alive : g->dead;
            else
                next[r][c] = (n == 3) ? g->alive : g->dead;
        }
    }

    /* troca os tabuleiros */
    free_board(g);
    g->board = next;
    return 0;
}

/* ---------- output ---------- */

void print_board(const t_game *g)
{
    int r, c;

    for (r = 0; r < g->height; r++)
    {
        for (c = 0; c < g->width; c++)
            putchar(g->board[r][c]);
        putchar('\n');
    }
}

/* ---------- main ---------- */

int main(int argc, char *argv[])
{
    t_game g;
    int    it;

    if (argc != 4)
        return 1;

    if (init_game(&g, argv) == -1)
        return 1;

    fill_board(&g);

    for (it = 0; it < g.iterations; it++)
    {
        if (step_game(&g) == -1)
        {
            free_board(&g);
            return 1;
        }
    }

    print_board(&g);
    free_board(&g);
    return 0;
}

