#include "../so_long.h"

int	is_wall(int x, int y, t_data *data)
{
	int	map_x;
	int	map_y;

	map_x = x / TILE_SIZE;
	map_y = y / TILE_SIZE;
	if (map_x >= 0 && map_x < data->map_width && map_y >= 0
		&& map_y < data->map_height)
	{
		return (data->map[map_y][map_x] == 1);
	}
	return (1); // Considera fora do mapa como parede
}

void	update_position_and_image(int keycode, t_data *data, int *new_x, int *new_y)
{
	if (keycode == 'a')
	{ // seta para a esquerda
		*new_x -= TILE_SIZE;
		data->img_player_current = data->img_player_left[data->frame];
	}
	else if (keycode == 'd')
	{ // seta para a direita
		*new_x += TILE_SIZE;
		data->img_player_current = data->img_player_right[data->frame];
	}
	else if (keycode == 'w')
	{ // seta para cima
		*new_y -= TILE_SIZE;
		data->img_player_current = data->img_player_up[data->frame];
	}
	else if (keycode == 's')
	{ // seta para baixo
		*new_y += TILE_SIZE;
		data->img_player_current = data->img_player_down[data->frame];
	}
}

int	key_event(int keycode, t_data *data)
{
	int	new_x;
	int	new_y;

	new_x = data->x;
	new_y = data->y;
	if (keycode == 65307)
		exit(0);

	update_position_and_image(keycode, data, &new_x, &new_y);// Atualiza a posição e imagem do jogador

	if (!is_wall(new_x, new_y, data))
	{// Se não for parede, atualiza a posição do jogador
		mlx_put_image_to_window(data->mlx, data->win, data->img_floor, data->x, data->y); // Limpa a posição atual
		data->x = new_x;
		data->y = new_y;
		mlx_put_image_to_window(data->mlx, data->win, data->img_player_current, data->x, data->y); // Desenha o jogador na nova posição
		data->frame = (data->frame + 1) % 3; // Avança para o próximo frame (assumindo 3 frames por direção)
	}
	return (0);
}
