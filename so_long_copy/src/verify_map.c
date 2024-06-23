/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 12:32:40 by tales             #+#    #+#             */
/*   Updated: 2024/06/23 13:57:02 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../so_long.h"


int is_valid_cell(int x, int y, t_data *data, int **visited)
{
    if (x >= 0 && x < data->map_width && y >= 0 && y < data->map_height
        && data->map[y][x] != 1 && !visited[y][x])
        return (1);
    return (0);
}


void dfs(int x, int y, t_data *data, int **visited)
{
    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int i;

    if (!is_valid_cell(x, y, data, visited))
        return;
    visited[y][x] = 1;
    if (data->map[y][x] == 2)
        data->collectibles_count--;
    i = 0;
    while (i < 4)
    {
        dfs(x + directions[i][0], y + directions[i][1], data, visited);
        i++;
    }
}

int **initialize_visited(int width, int height)
{
    int **visited;
    int i;

    visited = malloc(height * sizeof(int *));
    i = 0;
    while (i < height)
    {
        visited[i] = calloc(width, sizeof(int));
        i++;
    }
    return (visited);
}

int can_collect_all_and_reach_exit(t_data *data)
{
    int **visited;
    int player_x = -1, player_y = -1;
    int y = 0, x = 0;
    int exit_reachable = 0;
    int result;
    int i;

    visited = initialize_visited(data->map_width, data->map_height);
    
    // Reinitialize collectibles_count
    int original_collectibles_count = 0;
    while (y < data->map_height)
    {
        x = 0;
        while (x < data->map_width)
        {
            if (data->map[y][x] == 2)
                original_collectibles_count++;
            if (data->map[y][x] == 4)
            {
                player_x = x;
                player_y = y;
            }
            x++;
        }
        y++;
    }
    data->collectibles_count = original_collectibles_count;

    dfs(player_x, player_y, data, visited);

    y = 0;
    while (y < data->map_height)
    {
        x = 0;
        while (x < data->map_width)
        {
            if (data->map[y][x] == 3 && visited[y][x])
                exit_reachable = 1;
            x++;
        }
        y++;
    }

    result = (data->collectibles_count == 0 && exit_reachable);

    i = 0;
    while (i < data->map_height)
    {
        free(visited[i]);
        i++;
    }
    free(visited);
    return (result);
}
