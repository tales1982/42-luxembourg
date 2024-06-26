/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:25:20 by tlima-de          #+#    #+#             */
/*   Updated: 2024/05/31 18:25:22 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	load_image(void **img, void *mlx, char *path, t_data *data)
{// Carrega uma imagem
	*img = mlx_xpm_file_to_image(mlx, path, &data->img_width, &data->img_height);
	if (!(*img))
	{
		printf("Error loading image: %s\n", path);
		exit(1);
	}
}

void initialize_direction_images(t_data *data, void *sprite_sheet, int sprite_width, int sprite_height)
{// Inicializa as imagens de cada direção do player
    int i = 0;
    t_image_data img_data;
    img_data.mlx = data->mlx;
    img_data.src_img = sprite_sheet;
    img_data.width = sprite_width;
    img_data.height = sprite_height;

    while (i < 3)
    {
        data->img_player_down[i] = mlx_new_image(data->mlx, sprite_width, sprite_height);
        data->img_player_left[i] = mlx_new_image(data->mlx, sprite_width, sprite_height);
        data->img_player_right[i] = mlx_new_image(data->mlx, sprite_width, sprite_height);
        data->img_player_up[i] = mlx_new_image(data->mlx, sprite_width, sprite_height);

        img_data.dest_img = data->img_player_down[i];
        img_data.src_x = i * sprite_width;
        img_data.src_y = 0;
        copy_image_part(&img_data);

        img_data.dest_img = data->img_player_left[i];
        img_data.src_y = sprite_height;
        copy_image_part(&img_data);

        img_data.dest_img = data->img_player_right[i];
        img_data.src_y = 2 * sprite_height;
        copy_image_part(&img_data);

        img_data.dest_img = data->img_player_up[i];
        img_data.src_y = 3 * sprite_height;
        copy_image_part(&img_data);

        i++;
    }
}

void	initialize_images(t_data *data)
{// Inicializa as imagens do jogo
	void	*sprite_sheet;
	int		sprite_width;
	int		sprite_height;

	load_image(&sprite_sheet, data->mlx, "./img/pacMan.xpm", data);// Carrega a imagem do player com todas as direções
	sprite_width = data->img_width / 3;// Calcula a largura e altura de cada sprite
	sprite_height = data->img_height / 4;// Calcula a largura e altura de cada sprite
	initialize_direction_images(data, sprite_sheet, sprite_width, sprite_height);// Inicializa as imagens de cada direção do player
	data->img_player_current = data->img_player_down[0]; // Inicializa com a primeira imagem olhando para baixo
	data->frame = 0;// Inicializa o frame
	load_image(&data->img_floor, data->mlx, "./img/0.xpm", data);// Carrega a imagem do chão
	load_image(&data->img_wall, data->mlx, "./img/1.xpm", data);// Carrega a imagem da parede
}

void	start_game(t_data *data)
{// Inicializa o jogo
	data->mlx = mlx_init();// Inicializa a conexão com o servidor gráfico
	data->win = mlx_new_window(data->mlx, data->map_width * TILE_SIZE, data->map_height * TILE_SIZE, "So Long");// Cria uma janela
	initialize_images(data);// Inicializa as imagens do jogo
	data->x = 1 * TILE_SIZE;// Inicializa a posição do player
	data->y = 1 * TILE_SIZE;// Inicializa a posição do player
	draw_map(data);// Desenha o mapa
	mlx_put_image_to_window(data->mlx, data->win, data->img_player_current, data->x, data->y);// Coloca a imagem do player na janela
	mlx_key_hook(data->win, key_event, data);// Adiciona o evento de tecla pressionada
	mlx_hook(data->win, 17, 0, close_window, data);// Adiciona o evento de fechar a janela
	mlx_loop(data->mlx);// Inicia o loop de eventos
}
