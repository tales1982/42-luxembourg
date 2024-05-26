#include "../so_long.h"

int	*parse_line_to_map(const char *line, int width)
{// Converte uma linha do arquivo do mapa para um array de inteiros
	int	*map_row;
	int	i;

	map_row = malloc(sizeof(int) * width);
	i = 0;
	while (i < width)
	{
		if (line[i] == '1')
			map_row[i] = 1;
		else
			map_row[i] = 0;
		i++;
	}
	return (map_row);
}

int	**initialize_map(int width, int initial_height)
{// Inicializa o mapa
	int	**map;
    (void)width;
	map = malloc(sizeof(int *) * initial_height);
	return (map);
}

void	read_map_file(FILE *file, int **map, int *width, int *height)
{// Lê o arquivo do mapa
	char	*line;
	size_t	len;
	ssize_t	read;
	int		row;

	line = NULL;
	len = 0;
	row = 0;
	while ((read = getline(&line, &len, file)) != -1)
	{
		if (row == 0)
			*width = read - 1;
		map[row] = parse_line_to_map(line, *width);
		row++;
	}
	*height = row;
	free(line);
}

int	**load_map(const char *filename, int *width, int *height)
{// Carrega o mapa do arquivo
	int		fd;
	FILE	*file;
	int		**map;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	file = fdopen(fd, "r");
	if (!file)
		return (NULL);

	map = initialize_map(*width, 100); // Aloca memória para o mapa
	read_map_file(file, map, width, height);

	fclose(file);
	close(fd);
	return (map);
}
