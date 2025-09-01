#ifndef LIVE_H
# define LIVE_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_cell
{
	int now;
	int next;
}t_cell;

t_cell **s_board(int w, int h);
void free_board(t_cell **board, int w, int h);
void print_board(t_cell **board, int w, int h);
int neighbours(t_cell **board, int y, int x, int w, int h);
void iteneration(t_cell **board, int w, int h);

//void print_board_next(t_cell **board, int w, int h);
void change(t_cell **board, int w, int h);

#endif
