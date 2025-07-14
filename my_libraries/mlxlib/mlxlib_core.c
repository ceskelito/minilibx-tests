#include "mlxlib.h"
#include <string.h>

/* ========== CORE INSTANCE MANAGEMENT ========== */

t_mlx_instance *mlxlib_init(void)
{
	t_mlx_instance *instance;
	
	instance = malloc(sizeof(t_mlx_instance));
	if (!instance)
		return (NULL);
	
	instance->mlx_ptr = mlx_init();
	if (!instance->mlx_ptr)
	{
		free(instance);
		return (NULL);
	}
	
	instance->windows = NULL;
	instance->num_windows = 0;
	instance->loop_hook = NULL;
	instance->loop_param = NULL;
	instance->is_running = 0;
	instance->should_exit = 0;
	instance->user_data = NULL;
	
	return (instance);
}

int mlxlib_destroy(t_mlx_instance *instance)
{
	t_mlx_window *current;
	t_mlx_window *next;
	
	if (!instance)
		return (MLXLIB_NULL_PTR);
	
	/* Destroy all windows */
	current = instance->windows;
	while (current)
	{
		next = current->next;
		mlxlib_destroy_window(current);
		current = next;
	}
	
	/* Clean up MLX instance */
	if (instance->mlx_ptr)
	{
		mlx_destroy_display(instance->mlx_ptr);
		free(instance->mlx_ptr);
	}
	
	free(instance);
	return (MLXLIB_SUCCESS);
}

/* ========== WINDOW MANAGEMENT ========== */

static void add_window_to_instance(t_mlx_instance *instance, t_mlx_window *window)
{
	if (!instance->windows)
	{
		instance->windows = window;
		window->next = NULL;
		window->prev = NULL;
	}
	else
	{
		window->next = instance->windows;
		window->prev = NULL;
		instance->windows->prev = window;
		instance->windows = window;
	}
	instance->num_windows++;
}

static void remove_window_from_instance(t_mlx_instance *instance, t_mlx_window *window)
{
	if (!instance || !window)
		return;
	
	if (window->prev)
		window->prev->next = window->next;
	else
		instance->windows = window->next;
	
	if (window->next)
		window->next->prev = window->prev;
	
	instance->num_windows--;
}

t_mlx_window *mlxlib_new_window(t_mlx_instance *instance, int width, int height, char *title)
{
	t_mlx_window *window;
	
	if (!instance || !instance->mlx_ptr)
		return (NULL);
	
	window = malloc(sizeof(t_mlx_window));
	if (!window)
		return (NULL);
	
	/* Initialize window structure */
	window->win_ptr = mlx_new_window(instance->mlx_ptr, width, height, title);
	if (!window->win_ptr)
	{
		free(window);
		return (NULL);
	}
	
	/* Copy title */
	if (title)
	{
		window->title = malloc(strlen(title) + 1);
		if (window->title)
			strcpy(window->title, title);
	}
	else
		window->title = NULL;
	
	window->width = width;
	window->height = height;
	window->is_visible = 1;
	
	/* Initialize images array */
	window->images = NULL;
	window->num_images = 0;
	window->max_images = 0;
	
	/* Initialize event handlers to NULL */
	window->on_key_press = NULL;
	window->on_key_release = NULL;
	window->on_mouse_press = NULL;
	window->on_mouse_release = NULL;
	window->on_mouse_move = NULL;
	window->on_close = NULL;
	
	window->user_data = NULL;
	window->instance = instance;
	
	/* Add to instance */
	add_window_to_instance(instance, window);
	
	/* Set up default event hooks */
	mlx_hook(window->win_ptr, MLXLIB_DESTROY, 0, mlxlib_default_close_handler, window);
	
	return (window);
}

int mlxlib_destroy_window(t_mlx_window *window)
{
	int i;
	
	if (!window)
		return (MLXLIB_NULL_PTR);
	
	/* Destroy all images in this window */
	if (window->images)
	{
		for (i = 0; i < window->num_images; i++)
		{
			if (window->images[i])
				mlxlib_destroy_image(window, window->images[i]);
		}
		free(window->images);
	}
	
	/* Destroy MLX window */
	if (window->win_ptr && window->instance && window->instance->mlx_ptr)
		mlx_destroy_window(window->instance->mlx_ptr, window->win_ptr);
	
	/* Remove from instance */
	if (window->instance)
		remove_window_from_instance(window->instance, window);
	
	/* Free title */
	if (window->title)
		free(window->title);
	
	free(window);
	return (MLXLIB_SUCCESS);
}

int mlxlib_clear_window(t_mlx_window *window)
{
	if (!window || !window->win_ptr || !window->instance || !window->instance->mlx_ptr)
		return (MLXLIB_NULL_PTR);
	
	return (mlx_clear_window(window->instance->mlx_ptr, window->win_ptr));
}

/* ========== IMAGE MANAGEMENT ========== */

static int resize_images_array(t_mlx_window *window)
{
	t_data_img **new_array;
	int new_size;
	int i;
	
	new_size = window->max_images == 0 ? 4 : window->max_images * 2;
	new_array = malloc(sizeof(t_data_img*) * new_size);
	if (!new_array)
		return (MLXLIB_ERROR);
	
	/* Copy existing pointers */
	for (i = 0; i < window->num_images; i++)
		new_array[i] = window->images[i];
	
	/* Initialize new slots */
	for (i = window->num_images; i < new_size; i++)
		new_array[i] = NULL;
	
	free(window->images);
	window->images = new_array;
	window->max_images = new_size;
	
	return (MLXLIB_SUCCESS);
}

t_data_img *mlxlib_new_image(t_mlx_window *window, int width, int height)
{
	t_data_img *image;
	
	if (!window || !window->instance || !window->instance->mlx_ptr)
		return (NULL);
	
	image = malloc(sizeof(t_data_img));
	if (!image)
		return (NULL);
	
	/* Create MLX image */
	img_create(window->instance->mlx_ptr, image, width, height);
	if (!image->img)
	{
		free(image);
		return (NULL);
	}
	
	/* Add to window's images array */
	if (window->num_images >= window->max_images)
	{
		if (resize_images_array(window) != MLXLIB_SUCCESS)
		{
			mlx_destroy_image(window->instance->mlx_ptr, image->img);
			free(image);
			return (NULL);
		}
	}
	
	window->images[window->num_images] = image;
	window->num_images++;
	
	return (image);
}

int mlxlib_destroy_image(t_mlx_window *window, t_data_img *image)
{
	int i, j;
	
	if (!window || !image)
		return (MLXLIB_NULL_PTR);
	
	/* Find and remove image from window's array */
	for (i = 0; i < window->num_images; i++)
	{
		if (window->images[i] == image)
		{
			/* Destroy MLX image */
			if (image->img && window->instance && window->instance->mlx_ptr)
				mlx_destroy_image(window->instance->mlx_ptr, image->img);
			
			/* Shift remaining images */
			for (j = i; j < window->num_images - 1; j++)
				window->images[j] = window->images[j + 1];
			
			window->num_images--;
			free(image);
			return (MLXLIB_SUCCESS);
		}
	}
	
	return (MLXLIB_ERROR);
}

int mlxlib_put_image(t_mlx_window *window, t_data_img *image, int x, int y)
{
	if (!window || !image || !window->instance)
		return (MLXLIB_NULL_PTR);
	
	return (mlx_put_image_to_window(window->instance->mlx_ptr, window->win_ptr, image->img, x, y));
}

/* ========== UTILITY FUNCTIONS ========== */

t_mlx_window *mlxlib_find_window_by_ptr(t_mlx_instance *instance, void *win_ptr)
{
	t_mlx_window *current;
	
	if (!instance)
		return (NULL);
	
	current = instance->windows;
	while (current)
	{
		if (current->win_ptr == win_ptr)
			return (current);
		current = current->next;
	}
	
	return (NULL);
}

int mlxlib_get_window_count(t_mlx_instance *instance)
{
	if (!instance)
		return (0);
	return (instance->num_windows);
}

/* ========== DEFAULT EVENT HANDLERS ========== */

int mlxlib_default_close_handler(void *param)
{
	t_mlx_window *window = (t_mlx_window*)param;
	
	if (window && window->instance)
	{
		if (window->on_close)
			return (window->on_close(param));
		
		/* Default behavior: exit if this is the last window */
		if (window->instance->num_windows <= 1)
		{
			window->instance->should_exit = 1;
			exit(0);
		}
		else
		{
			mlxlib_destroy_window(window);
		}
	}
	
	return (0);
}

int mlxlib_default_key_handler(int keycode, void *param)
{
	t_mlx_window *window = (t_mlx_window*)param;
	
	/* Default ESC key behavior */
	if (keycode == MLXLIB_KEY_ESC)
	{
		if (window && window->instance)
		{
			window->instance->should_exit = 1;
			exit(0);
		}
	}
	
	return (0);
}