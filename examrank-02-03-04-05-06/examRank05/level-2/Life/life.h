#ifndef LIFE_H
#define LIFE_H

#include <stdlib.h>
#include <unistd.h>   /* read */
#include <stdio.h>    /* putchar */

typedef struct s_game
{
    int   width;
    int   height;
    int   iterations;
    char  alive;   /* 'O' */
    char  dead;    /* ' ' */
    int   i;       /* posição atual do "pincel" (linha)   */
    int   j;       /* posição atual do "pincel" (coluna)  */
    int   draw;    /* 0 = levantado, 1 = desenhando       */
    char **board;  /* matriz height x width                */
} t_game;

/* API */
int  init_game(t_game *g, char *argv[]);
void fill_board(t_game *g);
int  step_game(t_game *g);
void print_board(const t_game *g);
void free_board(t_game *g);

#endif /* LIFE_H */

