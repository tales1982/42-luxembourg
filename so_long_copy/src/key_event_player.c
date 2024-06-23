/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:14:00 by tales             #+#    #+#             */
/*   Updated: 2024/06/23 13:52:48 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	handle_exit(int keycode)
{
	if (keycode == 65307)
		exit(0);
}
void	update_collectibles(t_data *data, int new_x, int new_y)
{
	int	map_x;
	int	map_y;

	map_x = new_x / TILE_SIZE;
	map_y = new_y / TILE_SIZE;
	if (data->map[map_y][map_x] == 2)
	{
		data->collectibles_count--;
		data->map[map_y][map_x] = 0;
		if (data->collectibles_count == 0)
		{
			draw_exit(data);
		}
	}
}

void	check_victory(t_data *data, int new_x, int new_y)
{
	int	map_x;
	int	map_y;

	map_x = new_x / TILE_SIZE;
	map_y = new_y / TILE_SIZE;
	if (data->map[map_y][map_x] == 3 && data->collectibles_count == 0)
	{
		ft_printf("You win!\n");
		mlx_string_put(data->mlx, data->win, data->map_width * TILE_SIZE / 2
			- 50, data->map_height * TILE_SIZE / 2, 0xFFFFFF, "You win!");
		mlx_loop_end(data->mlx);
	}
}
