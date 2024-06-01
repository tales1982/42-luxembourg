/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:22:32 by tlima-de          #+#    #+#             */
/*   Updated: 2024/06/01 11:36:20 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	return (1);
}

void	update_position_and_image(int keycode, t_data *data, int *new_x,
		int *new_y)
{
	if (keycode == 'a')
	{
		*new_x -= TILE_SIZE;
		data->img_player_current = data->img_player_left[data->frame];
	}
	else if (keycode == 'd')
	{
		*new_x += TILE_SIZE;
		data->img_player_current = data->img_player_right[data->frame];
	}
	else if (keycode == 'w')
	{
		*new_y -= TILE_SIZE;
		data->img_player_current = data->img_player_up[data->frame];
	}
	else if (keycode == 's')
	{
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
	update_position_and_image(keycode, data, &new_x, &new_y);
	if (!is_wall(new_x, new_y, data))
	{
		mlx_put_image_to_window(data->mlx, data->win, data->img_floor, data->x,
			data->y);
		data->x = new_x;
		data->y = new_y;
		if (data->map[new_y / TILE_SIZE][new_x / TILE_SIZE] == 2)
		{
			data->collectibles_count--;
			data->map[new_y / TILE_SIZE][new_x / TILE_SIZE] = 0;
		}
		if (data->map[new_y / TILE_SIZE][new_x / TILE_SIZE] == 3
			&& data->collectibles_count == 0)
		{
			ft_printf("You win!\n");
			exit(0);
		}
		mlx_put_image_to_window(data->mlx, data->win, data->img_player_current,
			data->x, data->y);
		data->frame = (data->frame + 1) % 3;
	}
	return (0);
}

/*
° is_wall: Verifica se uma posição no mapa é uma parede.
° update_position_and_image: Atualiza a posição e a imagem do jogador com base na tecla pressionada.
° key_event: Trata os eventos de teclado para mover o jogador no mapa,
	atualizando a posição e a imagem se o movimento for válido.
*/