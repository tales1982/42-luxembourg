/* life.c — versão compacta, compatível com exame 42 */
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static int idx(int w, int i, int j) { return i * w + j; }

int main(int argc, char **argv)
{
    int w, h, iter, i, j, t;
    int x = 0, y = 0, pen = 0;
    char *board = NULL, *next = NULL, ch;

    if (argc != 4) return 1;
    w = atoi(argv[1]);
    h = atoi(argv[2]);
    iter = atoi(argv[3]);
    if (w <= 0 || h <= 0 || iter < 0) return 1;

    board = (char*)malloc((size_t)w * h);
    next  = (char*)malloc((size_t)w * h);
    if (!board || !next) { free(board); free(next); return 1; }

    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            board[idx(w, i, j)] = 0;

    /* desenha a semente com a “caneta” */
    while (read(0, &ch, 1) == 1)
    {
        int valid_cmd = 1;
        if      (ch == 'w') { if (y > 0)        y--; else valid_cmd = 0; }
        else if (ch == 's') { if (y < h - 1)    y++; else valid_cmd = 0; }
        else if (ch == 'a') { if (x > 0)        x--; else valid_cmd = 0; }
        else if (ch == 'd') { if (x < w - 1)    x++; else valid_cmd = 0; }
        else if (ch == 'x') { pen = !pen; }
        else valid_cmd = 0;

        if (pen && valid_cmd)
            board[idx(w, y, x)] = 1;
    }

    /* iterações do Game of Life */
    for (t = 0; t < iter; t++)
    {
        for (i = 0; i < h; i++)
        {
            for (j = 0; j < w; j++)
            {
                int n = 0, di, dj;
                for (di = -1; di <= 1; di++)
                    for (dj = -1; dj <= 1; dj++)
                        if ((di || dj)
                            && i + di >= 0 && i + di < h
                            && j + dj >= 0 && j + dj < w)
                            n += board[idx(w, i + di, j + dj)];
                next[idx(w, i, j)] =
                    (board[idx(w, i, j)] ? (n == 2 || n == 3) : (n == 3));
            }
        }
        /* swap buffers */
        { char *tmp = board; board = next; next = tmp; }
    }

    /* saída */
    for (i = 0; i < h; i++)
    {
        for (j = 0; j < w; j++)
            putchar(board[idx(w, i, j)] ? '0' : ' ');
        putchar('\n');
    }

    free(board);
    free(next);
    return 0;
}

