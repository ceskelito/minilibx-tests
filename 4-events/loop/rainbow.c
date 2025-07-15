#include "mlx.h"
#include "datalib.h"
#include "colors.h"
#include <stdlib.h>

typedef struct s_param{
	t_data		*data;
	t_data_img	*img;
} t_param;

void set_background(t_data_img *img, int color)
{
	int x;
	int y;

	x = 0;
	y = 0;

	for(y = 0; y < WINDOW_HEIGTH; y++)
		for(x = 0; x < WINDOW_LENGTH; x++)
			img_put_pixel(img, x, y, color);
}

void no_set_background(t_data_img *img, int color)
{
	char	*dest;
	int		i;

	dest = img->addr;
	i = 0;
	while(dest[i])
	{
		dest[i] = color;
		i++;
	}
}

int	handle_destroynotify(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
}

int change_background(t_param *param)
{
	static int	i = 0;
	if (param->img && param->img[i].img)
		mlx_put_image_to_window(param->data->mlx, param->data->win,
								param->img[i].img, 0, 0);
	i++;
	if (i > 2)
		i = 0;
	return (0);
}

int main(void)
{
	t_data		data;
	t_data_img	*img;
	t_param		param;

	data = data_init(NULL, WINDOW_LENGTH, WINDOW_HEIGTH, "Rainbow!!!");
	
	img = malloc(3 * sizeof(t_data_img));
	if(!img)
		return(1);
	img_create(data.mlx, &(img[0]), WINDOW_LENGTH, WINDOW_HEIGTH);
	img_create(data.mlx, &(img[1]), WINDOW_LENGTH, WINDOW_HEIGTH);
	img_create(data.mlx, &(img[2]), WINDOW_LENGTH, WINDOW_HEIGTH);

	set_background(&(img[0]), COLOR_GREEN);
	set_background(&(img[1]), COLOR_BLUE);
	set_background(&(img[2]), COLOR_RED);
	
	param.data = &data;
	param.img = img;

	mlx_loop_hook(data.mlx, &change_background, &param);
	mlx_hook(data.win, 17, 1L<<17, &handle_destroynotify, &data);

	mlx_loop(data.mlx);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
	return (0);
}
