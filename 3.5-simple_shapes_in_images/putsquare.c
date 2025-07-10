#include "mlx.h"
#include "imglib.h"

void img_put_square(t_data *img, int size, int x, int y, int color)
{

	for(int i = 0; i < size; i++)
	{
		img_put_pixel(img, x + i , y, color);
	}
}

int	main(void)
{
	void	*mlx;
	void	*window;
	t_data	img;

	mlx = mlx_init();
	window = mlx_new_window(mlx, 1920, 1080, "Hello, Square!");

	window = (void *)window; // Remove the "set but not used" error

	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(&img.img, &img.bits_per_pixel, &img.line_lenght,
																&img.endian);

	img_put_square(&img, 10, 100, 100, 0255255255);

	mlx_loop(mlx);
}
