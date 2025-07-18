#include "mlx.h"
#include "colors.h"
#include "imglib.h"
#include <math.h>

/**
 * Draws a square outline on the image.
 *
 * @param img     Pointer to image data structure.
 * @param size    Length of the sides of the square (must be >= 2).
 * @param x       X coordinate of the top-left corner.
 * @param y       Y coordinate of the top-left corner.
 * @param color   32-bit integer representing the pixel color.
 */
void img_put_square(t_data *img, int size, int x, int y, int color)
{
    int i;

    if (size < 2)
        return; // A square must be at least 2x2

    // Top side
    for (i = 0; i < size; i++)
        img_put_pixel(img, x + i, y, color);

    // Bottom side
    for (i = 0; i < size; i++)
        img_put_pixel(img, x + i, y + size - 1, color);

    // Left and Right sides (excluding corners)
    for (i = 1; i < size - 1; i++)
    {
        img_put_pixel(img, x, y + i, color);               // Left
        img_put_pixel(img, x + size - 1, y + i, color);     // Right
    }
}

void img_put_circle(t_data *img, int radius, int x_center, int y_center, int color)
{
    int     i;
    int     x_p, y_p;
    float   angle;
    int     n_points = 2 * M_PI * radius;

    for (i = 0; i < n_points; i++)
    {
        angle = (2 * M_PI * i) / n_points;
        x_p = (int)(x_center + radius * cos(angle));
        y_p = (int)(y_center + radius * sin(angle));

        // Protezione contro accessi fuori immagine (1920x1080 hardcoded, oppure usa img->width/height)
        if (x_p >= 0 && x_p < 1920 && y_p >= 0 && y_p < 1080)
            img_put_pixel(img, x_p, y_p, color);
    }
}

void img_put_circle_not_working(t_data *img, int radius, int x, int y, int color)
{
	int		t;
	float	x_p;
	float	y_p;
	int		n_points;
	
	n_points = (int)(2 * M_PI * radius);
	for(t = 0; t < (int)(2 * M_PI) ; t += (int)(2 * M_PI / n_points))
	{
		x_p = x + radius * cos(t);
		y_p = y + radius * sin(t);
		img_put_pixel(img, x_p, y_p, color);
	}
}

int	main(void)
{
	void	*mlx;
	void	*window;
	t_data	shape;

	mlx = mlx_init();
	window = mlx_new_window(mlx, 1920, 1080, "Hello, Square!");

	img_init_data(&shape, mlx, 1920, 1080);

	img_put_square(&shape, 200, 100, 100, COLOR_GREEN);
	img_put_circle(&shape, 100, 450, 200, COLOR_RED);

	mlx_put_image_to_window(mlx, window, shape.img, 0, 0);

	mlx_loop(mlx);
}
