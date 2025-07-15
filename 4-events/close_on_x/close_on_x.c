#include "mlx.h"
#include "imglib.h"
#include <X11/keysymdef.h>
#include <stdlib.h>

typedef struct s_data{
	void	*mlx;
	void	*win;
} t_data;

int handle_no_event(void *data)
{
	if(data)
		return (0);
	else
		return (0);
}

int	handle_destroynotify(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	return(0);
}

int main(void)
{
	t_data data;
	
	data.mlx = mlx_init();
	if(!data.mlx)
		return (MLX_ERROR);
	data.win = mlx_new_window(data.mlx, 1920, 1080, "Close On X");
	if(!data.win)
		return (MLX_ERROR);
	
	mlx_loop_hook(data.mlx, &handle_no_event, &data);
	mlx_hook(data.win, 17, 1L<<17, &handle_destroynotify, &data);

	mlx_loop(data.mlx);

	mlx_destroy_display(data.mlx);
	free(data.mlx);
	return (0);

}
