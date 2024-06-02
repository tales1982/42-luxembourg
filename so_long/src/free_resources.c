/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 19:43:37 by tales             #+#    #+#             */
/*   Updated: 2024/06/01 19:50:39 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	free_resources(t_data *data)
{
    int i = 0;

    while (i < data->map_height)
    {
        if (data->map[i])
            free(data->map[i]);
        i++;
    }
    free(data->map);
    mlx_destroy_image(data->mlx, data->img_floor);
    mlx_destroy_image(data->mlx, data->img_wall);
    mlx_destroy_image(data->mlx, data->img_collectible);
    mlx_destroy_image(data->mlx, data->img_exit);
    i = 0;
    while (i < 3)
    {
        mlx_destroy_image(data->mlx, data->img_player_down[i]);
        mlx_destroy_image(data->mlx, data->img_player_left[i]);
        mlx_destroy_image(data->mlx, data->img_player_right[i]);
        mlx_destroy_image(data->mlx, data->img_player_up[i]);
        i++;
    }
    if (data->win)
        mlx_destroy_window(data->mlx, data->win);
    if (data->mlx)
        mlx_destroy_display(data->mlx);
    free(data->mlx);
}
