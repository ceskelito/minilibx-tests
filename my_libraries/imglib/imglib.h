#ifndef IMGLIB_H
# define IMGLIB_H

typedef struct s_img {
	void    *img;
	char    *addr;                                                            
	int     bits_per_pixel;
	int     line_length;
	int     endian; 
} t_img;

typedef struct s_data {
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
} t_data;

int		img_get_offset(t_img *img, int x, int y);
void	img_put_pixel(t_data *data, int x, int y, int color);
void	img_init(t_img *img, void *mlx, int x_length, int y_length);
void	img_init_data(t_data *data, void *mlx, int x_length, int y_length);

#endif
