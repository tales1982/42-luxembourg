#include "../so_long.h"

void	copy_image_part(void *mlx, void *src_img, void *dest_img, int src_x,
		int src_y, int width, int height)
{// Copia uma parte de uma imagem para outra
	char	*src_data;
	char	*dest_data;
	int		src_index;
	int		dest_index;
	(void)mlx;
	int src_bpp, src_size_line, src_endian;// Bits por pixel, tamanho da linha, endianess
	int dest_bpp, dest_size_line, dest_endian;// Bits por pixel, tamanho da linha, endianess
	src_data = mlx_get_data_addr(src_img, &src_bpp, &src_size_line,
			&src_endian);// Obtém os dados da imagem
	dest_data = mlx_get_data_addr(dest_img, &dest_bpp, &dest_size_line,
			&dest_endian);// Obtém os dados da imagem
	int y = 0;
	while (y < height)
	{// Copia cada pixel da imagem
		int x = 0;
		while (x < width)
		{// Copia cada pixel da imagem
			src_index = ((src_y + y) * src_size_line) + ((src_x + x) * (src_bpp
						/ 8));
			dest_index = (y * dest_size_line) + (x * (dest_bpp / 8));
			int i = 0;
			while (i < (src_bpp / 8))
			{
				dest_data[dest_index + i] = src_data[src_index + i];
				i++;
			}
			x++;
		}
		y++;
	}
}
