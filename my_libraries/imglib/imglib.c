#include "imglib.h"
#include "mlx.h"

int img_get_offset(t_img *img, int x, int y)
{
//	      offset for the line	    nbyte = nbit / 8
	return (y * img->line_length + x * (img->bits_per_pixel / 8));
}

void img_put_pixel(t_img *img, int x, int y, int color)
{
	char	*dest;

	dest = img->addr + img_get_offset(img, x, y);
	*(unsigned int *)dest = color;
}

void img_init(t_img *img, void* mlx, int img_length, int img_heigth)
{
	img->img = mlx_new_image(mlx, img_length, img_heigth);
	img->addr = mlx_get_img_addr(img->img, &img->bits_per_pixel, &img->line_length,
										&img->endian);
}
