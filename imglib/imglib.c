#include "imglib.h"
#include "mlx.h"

int img_get_offset(t_data *img, int x, int y)
{
//	      offset for the line	    nbyte = nbit / 8
	return (y * img->line_length + x * (img->bits_per_pixel / 8));
}

void img_put_pixel(t_data *img, int x, int y, int color)
{
	char	*dest;

	dest = img->addr + img_get_offset(img, x, y);
	*(unsigned int *)dest = color;
}

void img_init_data(t_data *img, void* mlx, int x_length, int y_length)
{
	img->img = mlx_new_image(mlx, x_length, y_length);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
										&img->endian);
}
