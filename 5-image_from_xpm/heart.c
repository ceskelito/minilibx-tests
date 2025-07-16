#include "datalib.h"
#include "mlx.h"
#include <stdlib.h>
#include <string.h>

typedef struct s_xpm
{
	char	*filename;
	int		width;
	int		heigth;
} t_xpm;

int	main(void)
{
	t_data		data;
	t_data_img	img;
	t_xpm		red_heart;

	red_heart.filename = strdup("./read_heart.xpm");

	data = data_init(NULL, WINDOW_LENGTH, WINDOW_HEIGTH, "Heart!Heart!Heart!");
	img.img = mlx_xpm_file_to_image(data.mlx, red_heart.filename,
				&(red_heart.width), &(red_heart.heigth));
	mlx_put_image_to_window(data.mlx, data.win, img.img, 10, 10);

	mlx_loop(data.mlx);
	mlx_destroy_window(data.mlx, data.win);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
	return (0);
}
