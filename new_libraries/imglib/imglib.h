#ifndef IMGLIB_H
# define IMGLIB_H

# define MLX_ERROR 1

typedef struct s_image {
	void    *img;
	char    *addr;                                                            
	int     bpp; //bits per pxel
	int     line_len;
	int     endian; 
} t_image;

typedef struct s_data {
	void	*mlx_ptr;
	void	*win_ptr;
	t_image	img;
} t_data;

int		img_get_offset(t_image *img, int x, int y);
void	img_pixel_put(t_image *img, int x, int y, int color);
void	img_create(t_data *data, int img_length, int img_heigth);

#endif
