#include "imglib.h"
#include "mlx.h"
#include <stdlib.h>

int img_get_offset(t_image *img, int x, int y)
{
//	      offset for the line	    nbyte = nbit / 8
	return (y * img->line_length + x * (img->bits_per_pixel / 8));
}

void img_put_pixel(t_image *img, int x, int y, int color)
{
	char	*dest;

	if(!img || !img->addr)
		exit(MLX_ERROR);
	dest = img->addr + img_get_offset(img, x, y);
	*(unsigned int *)dest = color;
}

void img_create(t_data *data, int img_length, int img_heigth)
{
	if(!data || !data->mlx_ptr)
		exit(MLX_ERROR);
	data->img.img = mlx_new_image(data->mlx_ptr, img_length, img_heigth);
		if(!data->img.img)
			exit(MLX_ERROR);
	data->img.addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
										&img->line_length, &img->endian);
}

