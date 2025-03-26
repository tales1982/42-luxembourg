/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_initializers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:11:12 by tales             #+#    #+#             */
/*   Updated: 2024/08/05 20:11:17 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	initialize_direction_images(t_data *data, void *sprite_sheet,
		t_sprite_dim dim)
{
	int				i;
	t_image_data	img_data;

	initialize_image_data(&img_data, data, sprite_sheet, dim);
	i = 0;
	while (i < 3)
	{
		copy_sprite_images(data, &img_data, i, dim);
		i++;
	}
}

void	initialize_images(t_data *data)
{
	void			*sprite_sheet;
	t_sprite_dim	dim;

	load_image(&sprite_sheet, data->mlx, "./img/pacMan.xpm", data);
	dim.width = data->img_width / 3;
	dim.height = data->img_height / 4;
	initialize_direction_images(data, sprite_sheet, dim);
	data->img_player_current = data->img_player_down[0];
	data->frame = 0;
	load_image(&data->img_floor, data->mlx, "./img/0.xpm", data);
	load_image(&data->img_wall, data->mlx, "./img/1.xpm", data);
	load_image(&data->img_collectible, data->mlx, "./img/C.xpm", data);
	load_image(&data->img_exit, data->mlx, "./img/E.xpm", data);
}

void	initialize_player_position(t_data *data)
{
	data->x = 1 * TILE_SIZE;
	data->y = 1 * TILE_SIZE;
}

void	set_hooks_and_loop(t_data *data)
{
	mlx_key_hook(data->win, key_event, data);
	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_loop(data->mlx);
}

void	start_game(t_data *data)
{
	initialize_game_window(data);
	initialize_images(data);
	initialize_player_position(data);
	draw_map(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_player_current,
		data->x, data->y);
	set_hooks_and_loop(data);
}
