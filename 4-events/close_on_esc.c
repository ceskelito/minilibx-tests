#include "mlx.h"
#include "imglib.h"
#include <X11/keysym.h>
#include <stdlib.h>
#include <stdio.h>


typedef	struct s_param {
	void	*mlx;
	void	*win;
} t_param;


int	handle_no_event(void *data)
{
    /* This function needs to exist, but it is useless for the moment */
	if(data)
		return (0);
	else
		return (0);
}

int	handle_keypress(int keysym, t_param *data)
{

	// I'll take a KEYCODE. Need to convert into KEYSYM
	// keycode_to_keysym(keycode)
	
	if(keysym == XK_Escape)
		mlx_destroy_window(data->mlx, data->win);
	else
		printf("keysym: %i\n", keysym);
	return (0);
}

int main(void)
{
	void	*mlx;
	void	*win;
	t_param	data;

	mlx = mlx_init();
	if(!mlx)
		return(MLX_ERROR);
	win = mlx_new_window(mlx, 1920, 1080, "Close On Esc");
	if(!win)
		return(MLX_ERROR);
	data.mlx = mlx;
	data.win = win;
	
	mlx_loop_hook(mlx, &handle_no_event, &data);
	mlx_hook(win, 2, 1L<<0, &handle_keypress, &data);
	
	mlx_loop(mlx);
	
	mlx_destroy_display(mlx);
	free(mlx);
	return (0); 
}
