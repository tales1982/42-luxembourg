#include "live.h"



int main(int argc, char **argv)
{
	int 	w;
	int 	h;
	int		it;
	t_cell	**board;
	char	c;
	int		pen;
	int		y;
	int		x;
	
	if (argc != 4)
	{
		printf ("bad entry: > width heigth interactions-----\n");
		return (1);
	}

	//(void)argc;

	w = atoi(argv[1]);
	h = atoi(argv[2]);
	it = atoi(argv[3]);

	printf("&board adr: %p\n", &board);
	board = s_board(w, h);
	printf("board adr: %p\n", board);
	

	pen = 0;
	y = 0;
	x = 0;
	while (read (0, &c, 1) == 1)
	{
		if (c == 'w') y--;
		else if (c == 's') y++;
		else if (c == 'a') x--;
		else if (c == 'd') x ++;
		else if (c == 'x') pen = !pen;
		if (pen && y >= 0 && y < h && x >= 0 && x < w)
			board[y][x].now = 1;
	}


	for (int i = 0; i < it; i++)
	{
		iteneration(board, w, h);
		change(board, w, h);
	}
	
	print_board(board, w, h);
	//print_board_next(board, w, h);
	free_board(board, w, h);	
	return (0);
}



