#include "mlxlib.h"

/* ========== EVENT HANDLING SYSTEM ========== */

/* Internal event wrapper functions */
static int internal_key_handler(int keycode, void *param)
{
	t_mlx_window *window = (t_mlx_window*)param;
	
	if (!window)
		return (0);
	
	if (window->on_key_press)
		return (window->on_key_press(keycode, window->user_data));
	
	/* Call default handler */
	return (mlxlib_default_key_handler(keycode, param));
}

static int internal_key_release_handler(int keycode, void *param)
{
	t_mlx_window *window = (t_mlx_window*)param;
	
	if (!window)
		return (0);
	
	if (window->on_key_release)
		return (window->on_key_release(keycode, window->user_data));
	
	return (0);
}

static int internal_mouse_handler(int button, int x, int y, void *param)
{
	t_mlx_window *window = (t_mlx_window*)param;
	
	if (!window)
		return (0);
	
	if (window->on_mouse_press)
		return (window->on_mouse_press(button, x, y, window->user_data));
	
	return (0);
}

static int internal_mouse_release_handler(int button, int x, int y, void *param)
{
	t_mlx_window *window = (t_mlx_window*)param;
	
	if (!window)
		return (0);
	
	if (window->on_mouse_release)
		return (window->on_mouse_release(button, x, y, window->user_data));
	
	return (0);
}

static int internal_mouse_move_handler(int x, int y, void *param)
{
	t_mlx_window *window = (t_mlx_window*)param;
	
	if (!window)
		return (0);
	
	if (window->on_mouse_move)
		return (window->on_mouse_move(x, y, window->user_data));
	
	return (0);
}

/* ========== PUBLIC EVENT FUNCTIONS ========== */

int mlxlib_set_key_handler(t_mlx_window *window, t_key_handler handler, int event_type)
{
	if (!window || !window->win_ptr)
		return (MLXLIB_NULL_PTR);
	
	if (event_type == MLXLIB_KEY_PRESS)
	{
		window->on_key_press = handler;
		mlx_hook(window->win_ptr, KeyPress, KeyPressMask, internal_key_handler, window);
	}
	else if (event_type == MLXLIB_KEY_RELEASE)
	{
		window->on_key_release = handler;
		mlx_hook(window->win_ptr, KeyRelease, KeyReleaseMask, internal_key_release_handler, window);
	}
	else
		return (MLXLIB_ERROR);
	
	return (MLXLIB_SUCCESS);
}

int mlxlib_set_mouse_handler(t_mlx_window *window, t_mouse_handler handler, int event_type)
{
	if (!window || !window->win_ptr)
		return (MLXLIB_NULL_PTR);
	
	if (event_type == MLXLIB_MOUSE_PRESS)
	{
		window->on_mouse_press = handler;
		mlx_hook(window->win_ptr, ButtonPress, ButtonPressMask, internal_mouse_handler, window);
	}
	else if (event_type == MLXLIB_MOUSE_RELEASE)
	{
		window->on_mouse_release = handler;
		mlx_hook(window->win_ptr, ButtonRelease, ButtonReleaseMask, internal_mouse_release_handler, window);
	}
	else
		return (MLXLIB_ERROR);
	
	return (MLXLIB_SUCCESS);
}

int mlxlib_set_mouse_move_handler(t_mlx_window *window, t_mouse_move_handler handler)
{
	if (!window || !window->win_ptr)
		return (MLXLIB_NULL_PTR);
	
	window->on_mouse_move = handler;
	mlx_hook(window->win_ptr, MotionNotify, PointerMotionMask, internal_mouse_move_handler, window);
	
	return (MLXLIB_SUCCESS);
}

int mlxlib_set_close_handler(t_mlx_window *window, t_close_handler handler)
{
	if (!window || !window->win_ptr)
		return (MLXLIB_NULL_PTR);
	
	window->on_close = handler;
	/* The default close handler will call the custom handler if set */
	
	return (MLXLIB_SUCCESS);
}

static int internal_loop_hook(void *param)
{
	t_mlx_instance *instance = (t_mlx_instance*)param;
	
	if (!instance)
		return (0);
	
	if (instance->should_exit)
	{
		mlxlib_loop_end(instance);
		return (0);
	}
	
	if (instance->loop_hook)
		return (instance->loop_hook(instance->loop_param));
	
	return (0);
}

int mlxlib_set_loop_hook(t_mlx_instance *instance, t_loop_handler handler, void *param)
{
	if (!instance || !instance->mlx_ptr)
		return (MLXLIB_NULL_PTR);
	
	instance->loop_hook = handler;
	instance->loop_param = param;
	
	mlx_loop_hook(instance->mlx_ptr, internal_loop_hook, instance);
	
	return (MLXLIB_SUCCESS);
}

/* ========== LOOP MANAGEMENT ========== */

int mlxlib_loop(t_mlx_instance *instance)
{
	if (!instance || !instance->mlx_ptr)
		return (MLXLIB_NULL_PTR);
	
	instance->is_running = 1;
	instance->should_exit = 0;
	
	mlx_loop(instance->mlx_ptr);
	
	return (MLXLIB_SUCCESS);
}

int mlxlib_loop_end(t_mlx_instance *instance)
{
	if (!instance)
		return (MLXLIB_NULL_PTR);
	
	instance->should_exit = 1;
	instance->is_running = 0;
	
	/* Clean shutdown */
	mlxlib_destroy(instance);
	
	return (MLXLIB_SUCCESS);
}