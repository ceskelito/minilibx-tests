#include "mlx.h"

int main(void)
{
	void	*mlx;
	void	*mlx_window;

	mlx = mlx_init();
	mlx_window = mlx_new_window(mlx, 1920, 1080, "Hello, Pixels!");

	mlx_pixel_put(mlx, mlx_window, 100, 100, 0255255255);
	mlx_string_put(mlx, mlx_window, 200, 200, 0255255255, "Hello, Bastardi!");
	mlx_loop(mlx);
}
