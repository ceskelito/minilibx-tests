#include "mlx.h"
#include "datalib.h"
#include "colors.h"

#include <stdlib.h>
#include <X11/keysym.h>

#define SQUARE_SIDE	200

#define	LEFT	1
#define	RIGHT	2
#define	UP		3
#define	DOWN	4

/* Structure Definitions */
typedef struct s_sprite
{
	t_data_img	*img;
	int			x_pos;
	int			y_pos;
} t_sprite

typedef struct s_param
{
	t_data		*data;
	t_sprite	*sprite;
} t_param;

/*Function Definitions*/
int handle_loop(void *data)
{
	if(data)
		return (0);
	else
		return (0);
}

int	handle_destroynotify(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
}

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

void move_square(int dir, t_param *param)
{
	if(!param)
		exit(MLX_ERROR);
	switch(dir)
	{
		case (RIGHT):
			param->sprite->x_pos += 10;
			break;
		case (LEFT):
			param->sprite->x_pos -= 10;
			break;
		case (UP):
			param->sprite->y_pos += 10;
			break;
		case (DOWN):
			param->sprite->y_pos -= 10;
			break;
	}
	mlx_clear_window(param->data->mlx, param->data->win);
	mlx_
}

int handle_keypress(int keycode, t_param *param)
{
	if(!param)
		exit(MLX_ERROR);
	switch(keycode)
	{
		case (XK_Right):
		case (XK_d):
			move_square(RIGHT, param);
			break;
		case (XK_Left):
		case (XK_a):
			move_square(LEFT, param);
			break;
		case (XK_Down):
		case (XK_s):
			move_square(DOWN, param);
			break;
		case (XK_Up):
		case (XK_w):
			move_square(UP, param);
			break;
		default:
			break;
	}
	return (0);
}

void set_background(t_data_img *img, int color)
{
	int x;
	int y;

	x = 0;
	y = 0;

	for(y = 0; y < img->heigth; y++)
		for(x = 0; x < img->length; x++)
			img_put_pixel(img, x, y, color);
}

/* MAIN */
int main(void)
{
	t_data		data;
	t_data_img	back_g;
	t_data_img	square_img;
	t_sprite	square;
	t_param		param;


	square.img = &square_img;
	param.data = &data;
	param.sprite = &sprite;


	data = data_init(NULL, WINDOW_LENGTH, WINDOW_HEIGTH, "Move The Square!");

	img_create(data.mlx, &back_g, WINDOW_LENGTH, WINDOW_HEIGTH);
	img_create(data.mlx, square.img, SQUARE_SIDE, SQUARE_SIDE);

	img_set_background(&back_g, COLOR_ANTIQUEWHITE);
	img_set_background(square.img, COLOR_BLUE);

	mlx_put_image_to_window(data.mlx, data.win, back_g.img, 0, 0);
	mlx_put_image_to_window(data.mlx, data.win, square.img, 200, 200);
	square.x_pos = 200;
	square.y_pos = 200;

	mlx_hook(data.win, 2, 1L<<0, &handle_keypress, &param);
	mlx_hook(data.win, 17, 1L<<17, &handle_destroynotify, &data);
	mlx_loop_hook(data.mlx, &handle_loop, NULL);

	mlx_loop(data.mlx);

	mlx_destroy_window(data.mlx, data.win);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
	return(0);
}

