#include "mlx.h"
#include "so_long.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		printf("Usage: %s <map.ber>\n", argv[0]);
			// verifica se o arquivo map foi passado
		return (1);
	}
	data.map = load_map(argv[1], &data.map_width, &data.map_height);
		// carrega o arquivo map
	if (!data.map)
	{
		printf("Error loading map\n");
			// verifica se o arquivo map foi carregado
		return (1);
	}
	start_game(&data);
	return (0);
}
