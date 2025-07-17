#include "datalib.h"
#include "mlx.h"
#include "colors.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>


void draw_level(t_data *data, t_xpm *red_heart, t_xpm *rev_heart, t_param *p);

typedef struct s_xpm
{
	char	*filename;
	void	*img;
	int		width;
	int		heigth;
} t_xpm;

typedef struct param
{
	t_data	*data;
	t_xpm	*xpm;
	int		x_pos;
	int		y_pos;
} t_param;

int close_window(t_data *data)
{
    mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
    exit(0);
}

void new_level(t_param *p)
{
	int	x;
	int	y;

	x = WINDOW_LENGTH / 2 - 30;
	y = WINDOW_HEIGTH / 4;
	mlx_clear_window(p->data->mlx, p->data->win);
	mlx_put_image_to_window(p->data->mlx, p->data->win,
						p->xpm->img, p->x_pos, p->y_pos);
	mlx_string_put(p->data->mlx, p->data->win, x, y, COLOR_WHITE, "A G A I N");
	sleep(5);
	draw_level(p->data, p->red_heart, p->rev_heart, p);
}

int handle_mouse_click(int button, int x, int y, t_param *p)
{
	if(button == 1)
		if((x >= p->x_pos && x <= p->x_pos + p->xpm->width) &&
			(y >= p->y_pos && y <= p->y_pos + p->xpm->heigth))
		{
			new_level(p);
			return(1);
		}
	return(0);
}

void set_random_coordinates(int *x, int *y)
{
	srand(time(NULL));
	*x = (rand() % (WINDOW_LENGTH / 20)) * 20;
	*y = (rand() % (WINDOW_HEIGTH / 20)) * 20;
	if(*x > WINDOW_LENGTH || *y > WINDOW_HEIGTH)
		set_random_coordinates(x, y);
}

void draw_level(t_data *data, t_xpm *red_heart, t_xpm *rev_heart, t_param *p)
{
	set_random_coordinates(&(p->x_pos), &(p->y_pos));
	for(int i = 20; i < WINDOW_LENGTH - 20; i += 20)
		for(int j = 20; j < WINDOW_HEIGTH - 20; j += 20)
		{	
			if(i == p->x_pos && j == p->y_pos)
				mlx_put_image_to_window(data->mlx, data->win, rev_heart->img, i, j);
			else
				mlx_put_image_to_window(data->mlx, data->win, red_heart->img, i, j);
		}
}

int	main(void)
{
	t_data		data;
	t_xpm		red_heart;
	t_xpm		rev_heart;
	t_param		param;

	param.data = &data;
	param.xpm = &rev_heart;
	set_random_coordinates(&(param.x_pos), &(param.y_pos));
	printf("x: %i\ny: %i\n", param.x_pos, param.y_pos);

	data = data_init(NULL, WINDOW_LENGTH, WINDOW_HEIGTH, "Heart!Heart!Heart!");
	
	red_heart.filename = strdup("./red_heart.xpm");
	rev_heart.filename = strdup("./rev_heart.xpm");

	red_heart.img = mlx_xpm_file_to_image(data.mlx, red_heart.filename,
				&(red_heart.width), &(red_heart.heigth));
	rev_heart.img = mlx_xpm_file_to_image(data.mlx, rev_heart.filename,
				&(rev_heart.width), &(rev_heart.heigth));
	if(!red_heart.img || !rev_heart.img)
		return (MLX_ERROR);

	draw_level(&data, &red_heart, &rev_heart, &param);

	mlx_hook(data.win, 17, 1L<<17, &close_window, &data);
	mlx_mouse_hook(data.win, &handle_mouse_click, &param);
	mlx_loop(data.mlx);
	mlx_destroy_window(data.mlx, data.win);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
	return (0);
}
