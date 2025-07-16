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
	int	color;
	int	x_pos;
	int	y_pos;
} t_sprite;

typedef struct s_param
{
	t_data		*data;
	t_data_img	*img;
	t_sprite	*sprite;
} t_param;

void create_img_complete(t_param *p);

/*Function Definitions*/
int render(t_param *p)
{
	if(!p)
		exit(MLX_ERROR);
	
	mlx_clear_window(p->data->mlx, p->data->win);
	mlx_put_image_to_window(p->data->mlx, p->data->win, p->img->img, 0, 0);
	return (0);
}

int	handle_destroynotify(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
}

void img_put_square(t_data_img *img, int size, int x, int y, int color)
{
    for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
			img_put_pixel(img, x + i, y + j, color);
}

static void move_square(int dir, t_param *param)
{
	int *x;
	int *y;
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
			param->sprite->y_pos -= 10;
			break;
		case (DOWN):
			param->sprite->y_pos += 10;
			break;
	}
	y = &(param->sprite->y_pos);
	x = &(param->sprite->x_pos);
	if(*y < 0)
		*y = 0;
	if(*y > WINDOW_HEIGTH - SQUARE_SIDE)
		*y = WINDOW_HEIGTH - SQUARE_SIDE;
	if(*x < 0)
		*x = 0;
	if(*x > WINDOW_LENGTH - SQUARE_SIDE)
		*x = WINDOW_LENGTH -SQUARE_SIDE;
	mlx_destroy_image(param->data->mlx, param->img->img);
	create_img_complete(param);
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

void create_img_complete(t_param *p)
{
	img_create(p->data->mlx, p->img, WINDOW_LENGTH, WINDOW_HEIGTH);
	img_set_background(p->img, COLOR_ANTIQUEWHITE);
	img_put_square(p->img, SQUARE_SIDE, p->sprite->x_pos, p->sprite->y_pos, p->sprite->color);
}

/* MAIN */
int main(void)
{
	t_data		data;
	t_data_img	img;
	t_sprite	square;
	t_param		param;

	data = data_init(NULL, WINDOW_LENGTH, WINDOW_HEIGTH, "Move The Square!");

	square.color = COLOR_BLUE;
	square.x_pos = 200;
	square.y_pos = 200;

	param.data = &data;
	param.img = &img;
	param.sprite = &square;

	create_img_complete(&param);

	mlx_hook(data.win, 2, 1L<<0, &handle_keypress, &param);
	mlx_hook(data.win, 17, 1L<<17, &handle_destroynotify, &data);
	mlx_loop_hook(data.mlx, &render, &param);

	mlx_loop(data.mlx);

	mlx_destroy_window(data.mlx, data.win);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
	return(0);
}

