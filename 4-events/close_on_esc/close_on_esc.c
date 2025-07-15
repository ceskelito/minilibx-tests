#include "mlx.h"
#include "imglib.h"
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef X11_DISPLAY_ERROR
# define X11_DISPLAY_ERROR 2
#endif

typedef	struct s_param {
	void	*mlx;
	void	*win;
	Display	*display;
} t_param;


int	handle_no_event(void *data)
{
    /* This function needs to exist, but it is useless for the moment */
	if(data)
		return (0);
	else
		return (0);
}

int	handle_keypress(int keycode, t_param *data)
{
	if(keycode == XK_Escape)
		mlx_destroy_window(data->mlx, data->win);
	return (0);
}

int main(void)
{
	t_param	data;

	data.mlx = mlx_init();
	if(!data.mlx)
		return(MLX_ERROR);
	data.win = mlx_new_window(data.mlx, 1920, 1080, "Close On Esc");
	if(!data.win)
		return(MLX_ERROR);
	data.display = XOpenDisplay(NULL);
	if(!data.display)
		return (X11_DISPLAY_ERROR);
	
	mlx_loop_hook(data.mlx, &handle_no_event, &data);
	mlx_hook(data.win, 2, 1L<<0, &handle_keypress, &data);
	
	mlx_loop(data.mlx);
	
	mlx_destroy_display(data.mlx);
	free(data.mlx);
	return (0); 
}
