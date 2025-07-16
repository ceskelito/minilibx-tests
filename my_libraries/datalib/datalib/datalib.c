#include "datalib.h"
#include "mlx.h"

#ifndef LOCAL_DATA_STRUCT
t_data data_init(void *mlx_ptr, int w_l, int w_h, char *w_name)
{
	t_data data;

	if(mlx_ptr != NULL)
		data.mlx = mlx_ptr;
	else
		data.mlx = mlx_init();
	if(!data.mlx)
		exit(MLX_ERROR);
	data.win = mlx_new_window(data.mlx, w_l, w_h, w_name);
	if(!data.win)
	{
		free(data.mlx);
		exit(MLX_ERROR);
	}
	return (data);
}
#endif
