/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_loaders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:10:56 by tales             #+#    #+#             */
/*   Updated: 2024/08/05 20:10:59 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	load_image(void **img, void *mlx, char *path, t_data *data)
{
	*img = mlx_xpm_file_to_image(mlx, path, &data->img_width,
			&data->img_height);
	if (!(*img))
	{
		printf("Error loading image: %s\n", path);
		exit(1);
	}
}

void	create_images(t_data *data, int i, t_sprite_dim dim)
{
	data->img_player_down[i] = mlx_new_image(data->mlx, dim.width, dim.height);
	data->img_player_left[i] = mlx_new_image(data->mlx, dim.width, dim.height);
	data->img_player_right[i] = mlx_new_image(data->mlx, dim.width, dim.height);
	data->img_player_up[i] = mlx_new_image(data->mlx, dim.width, dim.height);
}

void	copy_sprite_part(t_image_data *img_data, int i, t_sprite_dim dim,
		int y_offset)
{
	img_data->src_x = i * dim.width;
	img_data->src_y = y_offset * dim.height;
	copy_image_part(img_data);
}

void	copy_sprite_images(t_data *data, t_image_data *img_data, int i,
		t_sprite_dim dim)
{
	create_images(data, i, dim);
	img_data->dest_img = data->img_player_down[i];
	copy_sprite_part(img_data, i, dim, 0);
	img_data->dest_img = data->img_player_left[i];
	copy_sprite_part(img_data, i, dim, 1);
	img_data->dest_img = data->img_player_right[i];
	copy_sprite_part(img_data, i, dim, 2);
	img_data->dest_img = data->img_player_up[i];
	copy_sprite_part(img_data, i, dim, 3);
}

void	initialize_image_data(t_image_data *img_data, t_data *data,
		void *sprite_sheet, t_sprite_dim dim)
{
	img_data->mlx = data->mlx;
	img_data->src_img = sprite_sheet;
	img_data->width = dim.width;
	img_data->height = dim.height;
}
