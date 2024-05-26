#ifndef SO_LONG_H
#define SO_LONG_H

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define TILE_SIZE 32

typedef struct s_data {
    void        *mlx;
    void        *win;
    int         **map;
    int         map_width;
    int         map_height;
    void        *img_floor;
    void        *img_wall;
    void        *img_player_left;
    void        *img_player_right;
    void        *img_player_current; // Current image for the player
    int         img_width;
    int         img_height;
    int         x;
    int         y;
}               t_data;

int close_window(void *param);
int key_event(int keycode, t_data *data);
void draw_map(t_data *data);
int **load_map(const char *filename, int *width, int *height);
void initialize_images(t_data *data);
void start_game(t_data data);
int is_wall(int x, int y, t_data *data);

#endif


