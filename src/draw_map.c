/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:22:21 by tlima-de          #+#    #+#             */
/*   Updated: 2024/05/31 18:22:23 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
