#include "mlx.h"

// Is a good practice to create a struct whit the image's data
typedef struct s_data
{

	void	*img;
	char	*addr;

	int		bits_per_pixel;
	int		line_lenght;
	int		endian;	
} t_data;

int mlx_get_offest(int x, int y, int bits_per_pixel, int line_lenght)
{
//	      offset for the line	    nbyte = nbit / 8
	return (y * line_lenght + x * (bits_per_pixel / 8));
}

void mlx_pixel_put_img(t_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + mlx_get_offest(x, y, img->bits_per_pixel, img->line_lenght);
	
	*(unsigned int *)dst = color;
}

int main(void)
{
	void		*mlx;
	void		*mlx_win;
	t_data		img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello, Images!");
/*

	* To retrieve image's data, i'll pass the image itself to mlx_get_data_addr(),
	* which will fill the other param according to the X server on the machine.
	* The function also return a pointer to the beginning of the memory area
	* in which the image is stored.													*/

	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_lenght,
																	&img.endian);	/*
	
	* From that pointer, we can reach every point of the image moving by
	* -bits_per_pixel- bits ecach time, and adding -line_lenght- to the pointer 
	* we will go to the beginning of the next line.

 */
	mlx_pixel_put_img(&img, 100, 100, 0255255255);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);

	mlx_loop(mlx);

	return 0;
}
