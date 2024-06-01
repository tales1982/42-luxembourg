/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 09:47:24 by tales             #+#    #+#             */
/*   Updated: 2024/06/01 11:38:01 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

# define TILE_SIZE 32

typedef struct s_data
{
    void    *mlx;
    void    *win;
    int     **map;
    int     map_width;
    int     map_height;
    void    *img_floor;
    void    *img_wall;
    void    *img_collectible;
    void    *img_exit;
    void    *img_player_up[3];
    void    *img_player_down[3];
    void    *img_player_left[3];
    void    *img_player_right[3];
    void    *img_player_current;
    int     img_width;
    int     img_height;
    int     x;
    int     y;
    int     frame;
    int     collectibles_count;
}           t_data;
typedef struct s_image_data
{
	void	*mlx;
	void	*src_img;
	void	*dest_img;
	int		src_x;
	int		src_y;
	int		width;
	int		height;
	char	*src_data;
	char	*dest_data;
	int		src_index;
	int		dest_index;
	int		y;
	int		x;
	int		i;
	int		src_size_line;
	int		src_endian;
	int		src_bpp;
	int		dest_bpp;
	int		dest_size_line;
	int		dest_endian;
}			t_image_data;

// inicialização
int			close_window(void *param);
void		initialize_game_window(t_data *data);
// copia de parte da imagem
void		draw_map(t_data *data);
// leitura do map
int			*parse_line_to_map(const char *line, int width);
int			**initialize_map(int width, int initial_height);
void		read_map_file(FILE *file, int **map, int *width, int *height);
int			**load_map(const char *filename, int *width, int *height);
// leitura de imagens
void		load_image(void **img, void *mlx, char *path, t_data *data);
void		initialize_direction_images(t_data *data, void *sprite_sheet,
				int sprite_width, int sprite_height);
void		initialize_images(t_data *data);
void		start_game(t_data *data);
// key_event
int			is_wall(int x, int y, t_data *data);
void		update_position_and_image(int keycode, t_data *data, int *new_x,
				int *new_y);
void		copy_image_part(t_image_data *data);
int			key_event(int keycode, t_data *data);
#endif
