#include "imglib.h"
#include "mlx.h"

int img_get_offset(t_img *img, int x, int y)
{
//	      offset for the line	    nbyte = nbit / 8
	return (y * img->line_length + x * (img->bits_per_pixel / 8));
}

void img_put_pixel(t_data *data, int x, int y, int color)
{
	char	*dest;

	dest = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dest = color;
}

void img_init(t_img *img, void* mlx, int img_length, int img_heigth)
{
	img->img = mlx_new_image(mlx, img_length, img_heigth);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
										&img->endian);
}

void img_init_data(t_data *data, void* mlx, int img_length, int img_heigth)
{
	data->mlx_ptr = mlx;
	data->img = mlx_new_image(mlx, img_length, img_heigth);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length,
										&data->endian);
}
