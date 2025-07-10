#include "imglib.h"

int img_get_offset(t_data *img, int x, int y)
{
//	      offset for the line	    nbyte = nbit / 8
	return (y * img->line_lenght + x * (img->bits_per_pixel / 8));
}

void img_put_pixel(t_data *img, int x, int y, int color)
{
	char	*dest;

	dest = img->addr + img_get_offset(img, x, y);
	*(unsigned int *)dest = color;
}
