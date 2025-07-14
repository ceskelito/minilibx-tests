#include "../my_libraries/mlxlib/mlxlib.h"
#include <stdio.h>

/* Global variables for the example */
typedef struct s_app_data
{
	t_mlx_instance	*mlx;
	t_mlx_window	*main_window;
	t_data_img	*canvas;
	t_gradient	*rainbow_grad;
	int		mouse_x;
	int		mouse_y;
	int		drawing_mode;
} t_app_data;

/* Event handlers */
int handle_key_press(int keycode, void *param)
{
	t_app_data *app = (t_app_data*)param;
	
	printf("Key pressed: %d\n", keycode);
	
	if (keycode == MLXLIB_KEY_ESC)
	{
		printf("ESC pressed, exiting...\n");
		mlxlib_loop_end(app->mlx);
		return (0);
	}
	else if (keycode == MLXLIB_KEY_W || keycode == MLXLIB_KEY_A || 
		 keycode == MLXLIB_KEY_S || keycode == MLXLIB_KEY_D)
	{
		printf("WASD movement key pressed\n");
	}
	else if (keycode == 32) /* Space bar */
	{
		printf("Space pressed - clearing canvas\n");
		mlxlib_clear_window(app->main_window);
		
		/* Redraw gradient background */
		mlxlib_draw_gradient_rectangle(app->canvas, 0, 0, 800, 600, app->rainbow_grad, 0);
		mlxlib_put_image(app->main_window, app->canvas, 0, 0);
	}
	else if (keycode >= 49 && keycode <= 51) /* Keys 1, 2, 3 */
	{
		app->drawing_mode = keycode - 48;
		printf("Drawing mode changed to: %d\n", app->drawing_mode);
	}
	
	return (0);
}

int handle_mouse_press(int button, int x, int y, void *param)
{
	t_app_data *app = (t_app_data*)param;
	t_gradient *local_grad;
	
	printf("Mouse button %d pressed at (%d, %d)\n", button, x, y);
	
	if (button == MLXLIB_MOUSE_LEFT)
	{
		switch (app->drawing_mode)
		{
			case 1: /* Draw circle */
				mlxlib_fill_circle(app->canvas, x, y, 30, COLOR_RED);
				break;
			case 2: /* Draw gradient circle */
				local_grad = mlxlib_create_gradient(COLOR_BLUE, COLOR_YELLOW, 50);
				mlxlib_draw_gradient_circle(app->canvas, x, y, 40, local_grad);
				mlxlib_destroy_gradient(local_grad);
				break;
			case 3: /* Draw rectangle */
				mlxlib_fill_rectangle(app->canvas, x - 25, y - 15, 50, 30, COLOR_GREEN);
				break;
			default:
				mlxlib_put_pixel_safe(app->canvas, x, y, COLOR_WHITE);
				break;
		}
		mlxlib_put_image(app->main_window, app->canvas, 0, 0);
	}
	
	return (0);
}

int handle_mouse_move(int x, int y, void *param)
{
	t_app_data *app = (t_app_data*)param;
	
	app->mouse_x = x;
	app->mouse_y = y;
	
	return (0);
}

int handle_close(void *param)
{
	t_app_data *app = (t_app_data*)param;
	
	printf("Window close requested\n");
	mlxlib_loop_end(app->mlx);
	return (0);
}

int render_loop(void *param)
{
	t_app_data *app = (t_app_data*)param;
	static int frame_count = 0;
	
	frame_count++;
	
	/* Update title with mouse position every 60 frames */
	if (frame_count % 60 == 0)
	{
		printf("Frame %d - Mouse at (%d, %d)\n", frame_count, app->mouse_x, app->mouse_y);
	}
	
	return (0);
}

int main(void)
{
	t_app_data app;
	
	printf("MLXLib Comprehensive Example\n");
	printf("Controls:\n");
	printf("  ESC - Exit\n");
	printf("  Space - Clear canvas\n");
	printf("  1 - Circle drawing mode\n");
	printf("  2 - Gradient circle mode\n");
	printf("  3 - Rectangle mode\n");
	printf("  Left click - Draw based on mode\n");
	printf("  Close button - Exit gracefully\n\n");
	
	/* Initialize MLX instance */
	app.mlx = mlxlib_init();
	if (!app.mlx)
	{
		printf("Error: Failed to initialize MLX\n");
		return (1);
	}
	
	/* Create main window */
	app.main_window = mlxlib_new_window(app.mlx, 800, 600, "MLXLib - Comprehensive Example");
	if (!app.main_window)
	{
		printf("Error: Failed to create window\n");
		mlxlib_destroy(app.mlx);
		return (1);
	}
	
	/* Create canvas image */
	app.canvas = mlxlib_new_image(app.main_window, 800, 600);
	if (!app.canvas)
	{
		printf("Error: Failed to create canvas\n");
		mlxlib_destroy(app.mlx);
		return (1);
	}
	
	/* Create rainbow gradient */
	app.rainbow_grad = mlxlib_create_gradient(COLOR_PURPLE, COLOR_CYAN, 100);
	if (!app.rainbow_grad)
	{
		printf("Error: Failed to create gradient\n");
		mlxlib_destroy(app.mlx);
		return (1);
	}
	
	/* Initialize app state */
	app.mouse_x = 0;
	app.mouse_y = 0;
	app.drawing_mode = 1;
	
	/* Set up event handlers */
	app.main_window->user_data = &app;
	mlxlib_set_key_handler(app.main_window, handle_key_press, MLXLIB_KEY_PRESS);
	mlxlib_set_mouse_handler(app.main_window, handle_mouse_press, MLXLIB_MOUSE_PRESS);
	mlxlib_set_mouse_move_handler(app.main_window, handle_mouse_move);
	mlxlib_set_close_handler(app.main_window, handle_close);
	mlxlib_set_loop_hook(app.mlx, render_loop, &app);
	
	/* Draw initial gradient background */
	mlxlib_draw_gradient_rectangle(app.canvas, 0, 0, 800, 600, app.rainbow_grad, 0);
	
	/* Draw some example shapes */
	mlxlib_draw_rectangle(app.canvas, 50, 50, 100, 80, COLOR_WHITE);
	mlxlib_fill_circle(app.canvas, 300, 150, 60, COLOR_RED);
	mlxlib_draw_circle(app.canvas, 500, 200, 80, COLOR_YELLOW);
	
	/* Show the canvas */
	mlxlib_put_image(app.main_window, app.canvas, 0, 0);
	
	printf("Starting main loop...\n");
	
	/* Start the main loop */
	mlxlib_loop(app.mlx);
	
	/* Cleanup */
	mlxlib_destroy_gradient(app.rainbow_grad);
	
	printf("Application ended gracefully\n");
	return (0);
}