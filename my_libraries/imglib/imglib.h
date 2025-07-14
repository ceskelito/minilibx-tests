#ifndef IMGLIB_H
# define IMGLIB_H

#define MLX_ERROR 1

typedef struct s_data_img
{
	void    *img;
	char    *addr;                                                            
	int     bpp; // bits per pixel
	int     line_len;
	int     endian; 
} t_data_img;

int		img_get_offset(t_data_img *img, int x, int y);
void	img_put_pixel(t_data_img *img, int x, int y, int color);
void	img_create(void *mlx, t_data_img *img, int img_length, int img_heigth);

#endif
