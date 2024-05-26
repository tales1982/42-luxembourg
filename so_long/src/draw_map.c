#include "../so_long.h"

void	draw_map(t_data *data)
{
	int y = 0;
	while (y < data->map_height)
	{
		int x = 0;
		while (x < data->map_width)
		{
			if (data->map[y][x] == 1)
			{
				mlx_put_image_to_window(data->mlx, data->win, data->img_wall, x
					* TILE_SIZE, y * TILE_SIZE); // desenha a parede
			}
			else
			{
				mlx_put_image_to_window(data->mlx, data->win, data->img_floor, x
					* TILE_SIZE, y * TILE_SIZE); // desenha o chão
			}
			x++;
		}
		y++;
	}
}