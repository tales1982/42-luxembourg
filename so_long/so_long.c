/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 09:46:13 by tales             #+#    #+#             */
/*   Updated: 2024/06/01 19:45:21 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void initialize_game_window(t_data *data)
{
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, data->map_width * TILE_SIZE,
            data->map_height * TILE_SIZE, "So Long");
}

int main(int argc, char **argv)
{
    t_data data;

    if (argc != 2)
    {
        printf("Usage: %s <map.ber>\n", argv[0]);
        return (1);
    }
    data.map = load_map(argv[1], &data.map_width, &data.map_height, &data);
    if (!data.map)
    {
        printf("Error loading map\n");
        return (1);
    }
	 data.move_count = 0; // Inicializa o contador de movimentos
    start_game(&data);
     free_resources(&data); // Libera os recursos alocados
    return (0);
}

/*
O código principal faz o seguinte:

Verifica os argumentos da linha de comando para garantir que o arquivo do mapa seja fornecido.
Carrega o mapa a partir do arquivo especificado.
Inicializa a janela do jogo e os recursos gráficos.
Inicia o jogo chamando a função start_game.
Fluxo do Programa
Inicialização:
initialize_game_window(data): Configura a janela do jogo.
Execução Principal:
main(argc, argv): Verifica os argumentos, carrega o mapa e inicia o jogo.
O programa é projetado para ser iniciado a partir da linha de comando com um argumento especificando o arquivo do mapa (por exemplo,
	./so_long map.ber). Se não for fornecido um argumento,
	ele exibe uma mensagem de uso e encerra. Se o mapa não puder ser carregado,
	ele exibe uma mensagem de erro e encerra. Se tudo estiver correto,
	ele inicializa a janela do jogo e inicia o jogo.
*/