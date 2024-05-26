#include "../so_long.h"

void initialize_images(t_data *data) {
    data->img_floor = mlx_xpm_file_to_image(data->mlx, "./img/0.xpm", &data->img_width, &data->img_height);
    data->img_wall = mlx_xpm_file_to_image(data->mlx, "./img/1.xpm", &data->img_width, &data->img_height);
    data->img_player_left = mlx_xpm_file_to_image(data->mlx, "./img/PA.xpm", &data->img_width, &data->img_height);
    data->img_player_right = mlx_xpm_file_to_image(data->mlx, "./img/PD.xpm", &data->img_width, &data->img_height);
    data->img_player_current = data->img_player_right; // Inicializa com a imagem olhando para a direita

    if (!data->img_floor || !data->img_wall || !data->img_player_left || !data->img_player_right) {
        printf("Error loading images\n");
        exit(1);
    }
}

void start_game(t_data data) {
    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, data.map_width * TILE_SIZE, data.map_height * TILE_SIZE, "Meu Jogo");

    initialize_images(&data);

    data.x = 1 * TILE_SIZE;
    data.y = 1 * TILE_SIZE;

    draw_map(&data);
    mlx_put_image_to_window(data.mlx, data.win, data.img_player_current, data.x, data.y);
    mlx_key_hook(data.win, key_event, &data);
    mlx_hook(data.win, 17, 0, close_window, &data);
    mlx_loop(data.mlx);
}

