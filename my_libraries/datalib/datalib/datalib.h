#ifndef DATALIB_H
# define DATALIB_H

# include "mlx.h"
# include "imglib.h"
# include <stdlib.h>

# define MLX_ERROR 1

# ifndef WINDOW_LENGTH
#  define WINDOW_LENGTH 1920
# endif

# ifndef WINDOW_HEIGTH
#  define WINDOW_HEIGTH 1080
# endif

# ifndef LOCAL_DATA_STRUCT
typedef struct s_data {
	void	*mlx;
	void	*win;
} t_data;

t_data data_init(void *mlx_ptr, int w_l, int w_h, char *w_name);
# endif





#endif
