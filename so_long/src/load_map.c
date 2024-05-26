#include "../so_long.h"

int	**load_map(const char *filename, int *width, int *height)
{
    int		fd;
    char	*line;
    size_t	len;
    ssize_t	read;
    int		**map;
    int		row;
    FILE	*file;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (NULL);
    line = NULL;
    len = 0;
    map = NULL;
    row = 0;
    file = fdopen(fd, "r");
    while ((read = getline(&line, &len, file)) != -1)
    {
        if (!map)
        {
            *width = read - 1;
            map = malloc(sizeof(int *) * 100);//aloca memória para o mapa
        }
        map[row] = malloc(sizeof(int) * (*width));//aloca memória para o mapa
        int i = 0;
        while (i < *width)
        {
            if (line[i] == '1')
                map[row][i] = 1;
            else
                map[row][i] = 0;
            i++;
        }
        row++;
    }
    *height = row;
    free(line);
    fclose(file);
    close(fd);
    return (map);
}
