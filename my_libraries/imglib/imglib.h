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

/*
typedef struct s_data_mlx
{
	// pointer to the actual istance of mlx
	void		*istance;

	// pointers to the first window/image linked to this istance of mlx
	void		*window;
	t_data_img	*image;
	
	// number of registered windos/images
	int			num_win;
	int			num_img;

	// current position in the windows/images pointer
	int			cur_win;
	int			cur_img;
} t_data_mlx
*/ //Don't know if useful, in doubt commented it 

int		img_get_offset(t_data_img *img, int x, int y);
void	img_put_pixel(t_data_img *img, int x, int y, int color);
void	img_create(void *mlx, t_data_img *img, int img_length, int img_heigth);

#endif
