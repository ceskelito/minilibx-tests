#ifndef IMGLIB_H
# define IMGLIB_H

typedef struct s_data
{
	void    *img;
	char    *addr;                                                            
	int     bits_per_pixel;
	int     line_length;
	int     endian; 
} t_data;

int		img_get_offset(t_data *img, int x, int y);
void	img_put_pixel(t_data *img, int x, int y, int color);
void	img_init_data(t_data *img, void *mlx, int x_length, int y_length);

#endif
