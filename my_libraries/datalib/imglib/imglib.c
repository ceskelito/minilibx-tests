#include "datalib.h"
#include "mlx.h"
#include <stdlib.h>


/*	*** TO-DO ***
 
 * Free the structs at exit
 
 */

int img_get_offset(t_data_img *img, int x, int y)
{
	if(!img)
		exit(MLX_ERROR);
	return (y * img->line_len + x * (img->bpp / 8));
}

void img_put_pixel(t_data_img *img, int x, int y, int color)
{
	char	*dest;

	if(!img || !img->addr)
		exit(MLX_ERROR);
	dest = img->addr + img_get_offset(img, x, y);
	if(!dest)
		exit(MLX_ERROR);
	*(unsigned int *)dest = color;
}

void img_create(void* mlx, t_data_img *img, int img_length, int img_heigth)
{
	if(!mlx || !img)
		exit(MLX_ERROR);
	img->img = mlx_new_image(mlx, img_length, img_heigth);
	if(!img->img)
		exit(MLX_ERROR);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
										&img->endian);
	if(!img->addr)
		exit(MLX_ERROR);
	img->length = img_length;
	img->heigth = img_heigth;
}

void img_set_background(t_data_img *img, int color)
{
	int x;
	int y;

	x = 0;
	y = 0;

	for(y = 0; y < img->heigth; y++)
		for(x = 0; x < img->length; x++)
			img_put_pixel(img, x, y, color);
}
