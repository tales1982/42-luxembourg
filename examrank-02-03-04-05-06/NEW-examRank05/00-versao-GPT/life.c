#include <stdlib.h> /* atoi, malloc, free */
#include <unistd.h> /* read */
#include <stddef.h> /* size_t */
#include <limits.h> /* INT_MAX */
#include <stdio.h>

/* Marca uma célula viva se (x,y) estiver no tabuleiro */
static void	set_alive(unsigned char *b, int w, int h, int x, int y, int pen)
{
	if (!pen)
		return ;
	if (x >= 0 && x < w && y >= 0 && y < h)
		b[y * w + x] = 1;
}

/* Conta vizinhos vivos com bordas mortas (fora do array = morto) */
static int	count_neighbors(const unsigned char *b, int w, int h, int x, int y)
{
	int dx, dy, nx, ny, n;

	n = 0;
	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			if (!(dx == 0 && dy == 0))
			{
				nx = x + dx;
				ny = y + dy;
				if (nx >= 0 && nx < w && ny >= 0 && ny < h)
					n += (b[ny * w + nx] != 0);
			}
			++dx;
		}
		++dy;
	}
	return (n);
}

/* Executa 1 iteração do Life: escreve em next a partir de cur */
static void	life_step(const unsigned char *cur, unsigned char *next, int w, int h)
{
	int x, y, n, alive, idx;

	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			idx = y * w + x;
			alive = (cur[idx] != 0);
			n = count_neighbors(cur, w, h, x, y);
			next[idx] = (unsigned char)((alive && (n == 2 || n == 3)) || (!alive && n == 3));
			++x;
		}
		++y;
	}
}

/* Imprime o tabuleiro com '0' para vivo e ' ' para morto + '\n' por linha */
static void	print_board(const unsigned char *b, int w, int h)
{
	int x, y;

	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			if (b[y * w + x])
				putchar('0');
			else
				putchar(' ');
			++x;
		}
		putchar('\n');
		++y;
	}
}

/* Processa comandos da stdin e desenha no buffer b */
static void	draw_from_stdin(unsigned char *b, int w, int h)
{
	char		buf[4096];
	ssize_t		n;
	int			px, py, pen; /* posição da caneta e estado (0=up, 1=down) */
	size_t		i;

	px = 0;
	py = 0;
	pen = 0;
	while ((n = read(0, buf, sizeof(buf))) > 0)
	{
		i = 0;
		while (i < (size_t)n)
		{
			char c = buf[i];
			if (c == 'x')
			{
				pen = !pen;
				set_alive(b, w, h, px, py, pen); /* marca posição atual ao abaixar */
			}
			else if (c == 'w' && py > 0)
			{
				--py;
				set_alive(b, w, h, px, py, pen);
			}
			else if (c == 's' && py < h - 1)
			{
				++py;
				set_alive(b, w, h, px, py, pen);
			}
			else if (c == 'a' && px > 0)
			{
				--px;
				set_alive(b, w, h, px, py, pen);
			}
			else if (c == 'd' && px < w - 1)
			{
				++px;
				set_alive(b, w, h, px, py, pen);
			}
			/* quaisquer outros chars (espaço, \n, etc.) são ignorados */
			++i;
		}
	}
}

/* Parse simples e seguro de inteiros positivos */
static int	parse_posint(const char *s)
{
	long v;

	v = (long)atoi(s);
	if (v <= 0 || v > INT_MAX)
		return (0);
	return ((int)v);
}

int	main(int argc, char **argv)
{
	int				w, h, iters, i;
	unsigned char	*cur;
	unsigned char	*next;
	unsigned char	*tmp;

	if (argc != 4)
		return (1);
	w = parse_posint(argv[1]);
	h = parse_posint(argv[2]);
	iters = parse_posint(argv[3]);
	if (w <= 0 || h <= 0 || iters < 0)
		return (1);
	cur = (unsigned char *)malloc((size_t)w * (size_t)h);
	next = (unsigned char *)malloc((size_t)w * (size_t)h);
	if (!cur || !next)
	{
		free(cur);
		free(next);
		return (1);
	}
	/* zera o tabuleiro inicial */
	{
		size_t sz = (size_t)w * (size_t)h, k = 0;
		while (k < sz) cur[k++] = 0;
	}
	draw_from_stdin(cur, w, h);
	i = 0;
	while (i < iters)
	{
		life_step(cur, next, w, h);
		tmp = cur;
		cur = next;
		next = tmp;
		++i;
	}
	print_board(cur, w, h);
	free(cur);
	free(next);
	return (0);
}
