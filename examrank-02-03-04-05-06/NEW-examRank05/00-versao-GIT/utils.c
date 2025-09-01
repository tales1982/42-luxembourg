#include "live.h"

t_cell **s_board(int w, int h)
{
	t_cell **board;

	board = calloc( h, sizeof(t_cell *));
	for (int i = 0; i < h; i++)
		board[i] = calloc (w, sizeof (t_cell));
	return (board);

}

void free_board(t_cell **board, int w, int h)
{
	//puts("freeee");
	//printf("free board adr: %p\n", board);
	for (int i = 0; i < h; i ++)
	{
		free (board[i]);
	}
	free (board);
}

void print_board(t_cell **board, int w, int h)
{
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (board[i][j].now == 1)
				putchar('0');
			else
				putchar (' ');
		}
		putchar('\n');
	}
}
/*
	(0,0)  (0,1)  (0,2)
	(1,0) *(1,1)* (1,2)
	(2,0)  (2,1)  (2,2)
*/
int neighbours(t_cell **board, int y, int x, int w, int h)
{
	int count;
	int yy;
	int xx;

	yy = y - 1;
	
	count = 0;
	for (int i = 0; i < 3; i++)
	{
		xx = x - 1;
		for (int j = 0; j < 3; j++)
		{
			if (xx == x && yy == y)
			{
				xx++;
				continue;
			}
			if (xx >= 0 && xx < w && yy >= 0 && yy < h)
				if (board[yy][xx].now == 1)
					count++;
			xx++;
		}
		yy++;
	}
	return (count);
}

void iteneration(t_cell **board, int w, int h)
{
	int count;
	int live;

	count = 0;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			live = board[i][j].now;
			count = neighbours(board, i, j, w, h);
			if ((live && ( count == 2 || count == 3)) || (!live && count == 3)) 
				board[i][j].next = 1;
			else
				board[i][j].next = 0;
		}
	}
}

void change(t_cell **board, int w, int h)
{
	for ( int i = 0; i < h; i++)
	{
		for ( int j = 0; j < w; j++)
		{
			board[i][j].now = board[i][j].next;
		}
	}
}

/*apenas para testar o segundo mapa*/
/*void print_board_next(t_cell **board, int w, int h)
{
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (board[i][j].next == 1)
				putchar('0');
			else
				putchar (' ');
		}
		putchar('\n');
	}
}*/
