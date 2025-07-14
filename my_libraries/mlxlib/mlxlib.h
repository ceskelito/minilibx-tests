#ifndef MLXLIB_H
# define MLXLIB_H

# include "mlx.h"
# include "../colors/colors.h"
# include "../imglib/imglib.h"
# include <stdlib.h>

/* Error codes */
# define MLXLIB_SUCCESS		0
# define MLXLIB_ERROR		1
# define MLXLIB_NULL_PTR	2
# define MLXLIB_INIT_ERROR	3

/* Window events */
# define MLXLIB_KEY_PRESS	2
# define MLXLIB_KEY_RELEASE	3
# define MLXLIB_MOUSE_PRESS	4
# define MLXLIB_MOUSE_RELEASE	5
# define MLXLIB_MOUSE_MOVE	6
# define MLXLIB_EXPOSE		12
# define MLXLIB_DESTROY		17

/* Common key codes */
# define MLXLIB_KEY_ESC		0xff1b
# define MLXLIB_KEY_LEFT	0xff51
# define MLXLIB_KEY_UP		0xff52
# define MLXLIB_KEY_RIGHT	0xff53
# define MLXLIB_KEY_DOWN	0xff54
# define MLXLIB_KEY_W		119
# define MLXLIB_KEY_A		97
# define MLXLIB_KEY_S		115
# define MLXLIB_KEY_D		100

/* Mouse buttons */
# define MLXLIB_MOUSE_LEFT	1
# define MLXLIB_MOUSE_MIDDLE	2
# define MLXLIB_MOUSE_RIGHT	3
# define MLXLIB_MOUSE_SCROLL_UP		4
# define MLXLIB_MOUSE_SCROLL_DOWN	5

/* Forward declarations */
typedef struct s_mlx_window	t_mlx_window;
typedef struct s_mlx_instance	t_mlx_instance;

/* Event callback function types */
typedef int (*t_key_handler)(int keycode, void *param);
typedef int (*t_mouse_handler)(int button, int x, int y, void *param);
typedef int (*t_mouse_move_handler)(int x, int y, void *param);
typedef int (*t_close_handler)(void *param);
typedef int (*t_loop_handler)(void *param);

/* Window structure */
typedef struct s_mlx_window
{
	void			*win_ptr;		/* MLX window pointer */
	char			*title;			/* Window title */
	int				width;			/* Window width */
	int				height;			/* Window height */
	int				is_visible;		/* Window visibility status */
	
	/* Images associated with this window */
	t_data_img		**images;		/* Array of images */
	int				num_images;		/* Number of images */
	int				max_images;		/* Maximum capacity */
	
	/* Event handlers */
	t_key_handler		on_key_press;
	t_key_handler		on_key_release;
	t_mouse_handler		on_mouse_press;
	t_mouse_handler		on_mouse_release;
	t_mouse_move_handler	on_mouse_move;
	t_close_handler		on_close;
	
	/* User data */
	void			*user_data;
	
	/* Parent instance reference */
	t_mlx_instance		*instance;
	
	/* Linked list pointers */
	t_mlx_window		*next;
	t_mlx_window		*prev;
} t_mlx_window;

/* MLX instance structure - manages everything */
typedef struct s_mlx_instance
{
	void			*mlx_ptr;		/* MLX instance pointer */
	
	/* Windows management */
	t_mlx_window		*windows;		/* Linked list of windows */
	int				num_windows;		/* Number of windows */
	
	/* Global event handlers */
	t_loop_handler		loop_hook;
	void			*loop_param;
	
	/* Instance status */
	int				is_running;
	int				should_exit;
	
	/* User data */
	void			*user_data;
} t_mlx_instance;

/* Gradient structure for color transitions */
typedef struct s_gradient
{
	int	start_color;	/* Starting color (TRGB) */
	int	end_color;	/* Ending color (TRGB) */
	int	steps;		/* Number of steps in gradient */
} t_gradient;

/* ========== CORE FUNCTIONS ========== */

/* Instance management */
t_mlx_instance	*mlxlib_init(void);
int		mlxlib_destroy(t_mlx_instance *instance);
int		mlxlib_loop(t_mlx_instance *instance);
int		mlxlib_loop_end(t_mlx_instance *instance);

/* Window management */
t_mlx_window	*mlxlib_new_window(t_mlx_instance *instance, int width, int height, char *title);
int		mlxlib_destroy_window(t_mlx_window *window);
int		mlxlib_show_window(t_mlx_window *window);
int		mlxlib_hide_window(t_mlx_window *window);
int		mlxlib_clear_window(t_mlx_window *window);

/* Image management */
t_data_img	*mlxlib_new_image(t_mlx_window *window, int width, int height);
int		mlxlib_destroy_image(t_mlx_window *window, t_data_img *image);
int		mlxlib_put_image(t_mlx_window *window, t_data_img *image, int x, int y);

/* Event system */
int		mlxlib_set_key_handler(t_mlx_window *window, t_key_handler handler, int event_type);
int		mlxlib_set_mouse_handler(t_mlx_window *window, t_mouse_handler handler, int event_type);
int		mlxlib_set_mouse_move_handler(t_mlx_window *window, t_mouse_move_handler handler);
int		mlxlib_set_close_handler(t_mlx_window *window, t_close_handler handler);
int		mlxlib_set_loop_hook(t_mlx_instance *instance, t_loop_handler handler, void *param);

/* ========== ENHANCED COLOR FUNCTIONS ========== */

/* Gradient functions */
int		mlxlib_gradient_color(t_gradient *grad, float position);
t_gradient	*mlxlib_create_gradient(int start_color, int end_color, int steps);
void		mlxlib_destroy_gradient(t_gradient *grad);

/* Color blending */
int		mlxlib_blend_colors(int color1, int color2, float ratio);
int		mlxlib_interpolate_rgb(int start_r, int start_g, int start_b, 
				      int end_r, int end_g, int end_b, float ratio);

/* Enhanced color utilities */
int		mlxlib_hsv_to_rgb(float h, float s, float v);
void		mlxlib_rgb_to_hsv(int rgb, float *h, float *s, float *v);
int		mlxlib_lighten_color(int color, float factor);
int		mlxlib_darken_color(int color, float factor);

/* ========== DRAWING UTILITIES ========== */

/* Basic shapes */
void		mlxlib_draw_line(t_data_img *img, int start[2], int end[2], int color);
void		mlxlib_draw_rectangle(t_data_img *img, int x, int y, int width, int height, int color);
void		mlxlib_draw_circle(t_data_img *img, int center_x, int center_y, int radius, int color);
void		mlxlib_fill_rectangle(t_data_img *img, int x, int y, int width, int height, int color);
void		mlxlib_fill_circle(t_data_img *img, int center_x, int center_y, int radius, int color);

/* Gradient shapes */
void		mlxlib_draw_gradient_rectangle(t_data_img *img, int x, int y, int width, int height, t_gradient *grad, int direction);
void		mlxlib_draw_gradient_circle(t_data_img *img, int center_x, int center_y, int radius, t_gradient *grad);

/* ========== UTILITY FUNCTIONS ========== */

/* Safe pixel operations with bounds checking */
int		mlxlib_put_pixel_safe(t_data_img *img, int x, int y, int color);
int		mlxlib_get_pixel(t_data_img *img, int x, int y);

/* Window utilities */
t_mlx_window	*mlxlib_find_window_by_ptr(t_mlx_instance *instance, void *win_ptr);
int		mlxlib_get_window_count(t_mlx_instance *instance);

/* Memory utilities */
void		mlxlib_cleanup_instance(t_mlx_instance *instance);
void		mlxlib_cleanup_window(t_mlx_window *window);

/* Default event handlers */
int		mlxlib_default_close_handler(void *param);
int		mlxlib_default_key_handler(int keycode, void *param);

#endif