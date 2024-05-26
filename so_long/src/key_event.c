#include "../so_long.h"

int is_wall(int x, int y, t_data *data) {
    int map_x = x / TILE_SIZE;
    int map_y = y / TILE_SIZE;
    
    if (map_x >= 0 && map_x < data->map_width && map_y >= 0 && map_y < data->map_height) {
        return data->map[map_y][map_x] == 1;
    }
    return 1; // Considera fora do mapa como parede
}

int key_event(int keycode, t_data *data) {
    int new_x = data->x;
    int new_y = data->y;

    if (keycode == 65307) { // ESC key
        exit(0);
    }

    if (keycode == 65361) { // seta para a esquerda
        new_x -= TILE_SIZE;
        data->img_player_current = data->img_player_left;
    } else if (keycode == 65363) { // seta para a direita
        new_x += TILE_SIZE;
        data->img_player_current = data->img_player_right;
    } else if (keycode == 65362) { // seta para cima
        new_y -= TILE_SIZE;
    } else if (keycode == 65364) { // seta para baixo
        new_y += TILE_SIZE;
    }

    if (!is_wall(new_x, new_y, data)) {
        mlx_put_image_to_window(data->mlx, data->win, data->img_floor, data->x, data->y); // Limpa a posição atual
        data->x = new_x;
        data->y = new_y;
        mlx_put_image_to_window(data->mlx, data->win, data->img_player_current, data->x, data->y); // Desenha o jogador na nova posição
    }

    return 0;
}
