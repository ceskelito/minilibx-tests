#include "imglib.h"
#include "mlx.h"
#include <stdlib.h>


/*	*** TO-DO ***
 
 * Free the structs at exit
 
 */

int img_get_offset(t_data_img *img, int x, int y)
{
	if(!img)
		exit(MLX_ERROR);
//	      offset for the line	    nbyte = nbit / 8
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
}
