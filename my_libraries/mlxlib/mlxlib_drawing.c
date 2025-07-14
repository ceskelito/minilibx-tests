#include "mlxlib.h"
#include <math.h>

/* ========== SAFE PIXEL OPERATIONS ========== */

int mlxlib_put_pixel_safe(t_data_img *img, int x, int y, int color)
{
	if (!img || !img->addr)
		return (MLXLIB_NULL_PTR);
	
	/* Simple bounds checking - we don't have width/height in t_data_img */
	if (x < 0 || y < 0)
		return (MLXLIB_ERROR);
	
	img_put_pixel(img, x, y, color);
	return (MLXLIB_SUCCESS);
}

int mlxlib_get_pixel(t_data_img *img, int x, int y)
{
	char *src;
	
	if (!img || !img->addr || x < 0 || y < 0)
		return (0);
	
	src = img->addr + img_get_offset(img, x, y);
	return (*(unsigned int *)src);
}

/* ========== BASIC SHAPES ========== */

void mlxlib_draw_line(t_data_img *img, int start[2], int end[2], int color)
{
	int dx, dy, sx, sy, err, e2;
	int x0, y0, x1, y1;
	
	if (!img)
		return;
	
	x0 = start[0]; y0 = start[1];
	x1 = end[0]; y1 = end[1];
	
	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	sx = x0 < x1 ? 1 : -1;
	sy = y0 < y1 ? 1 : -1;
	err = dx - dy;
	
	while (1)
	{
		mlxlib_put_pixel_safe(img, x0, y0, color);
		
		if (x0 == x1 && y0 == y1)
			break;
		
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void mlxlib_draw_rectangle(t_data_img *img, int x, int y, int width, int height, int color)
{
	int start[2], end[2];
	
	if (!img || width <= 0 || height <= 0)
		return;
	
	/* Top line */
	start[0] = x; start[1] = y;
	end[0] = x + width - 1; end[1] = y;
	mlxlib_draw_line(img, start, end, color);
	
	/* Bottom line */
	start[0] = x; start[1] = y + height - 1;
	end[0] = x + width - 1; end[1] = y + height - 1;
	mlxlib_draw_line(img, start, end, color);
	
	/* Left line */
	start[0] = x; start[1] = y;
	end[0] = x; end[1] = y + height - 1;
	mlxlib_draw_line(img, start, end, color);
	
	/* Right line */
	start[0] = x + width - 1; start[1] = y;
	end[0] = x + width - 1; end[1] = y + height - 1;
	mlxlib_draw_line(img, start, end, color);
}

void mlxlib_fill_rectangle(t_data_img *img, int x, int y, int width, int height, int color)
{
	int i, j;
	
	if (!img || width <= 0 || height <= 0)
		return;
	
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			mlxlib_put_pixel_safe(img, x + j, y + i, color);
		}
	}
}

void mlxlib_draw_circle(t_data_img *img, int center_x, int center_y, int radius, int color)
{
	int x, y, decision;
	
	if (!img || radius <= 0)
		return;
	
	x = 0;
	y = radius;
	decision = 3 - 2 * radius;
	
	while (x <= y)
	{
		/* Draw 8 octants */
		mlxlib_put_pixel_safe(img, center_x + x, center_y + y, color);
		mlxlib_put_pixel_safe(img, center_x - x, center_y + y, color);
		mlxlib_put_pixel_safe(img, center_x + x, center_y - y, color);
		mlxlib_put_pixel_safe(img, center_x - x, center_y - y, color);
		mlxlib_put_pixel_safe(img, center_x + y, center_y + x, color);
		mlxlib_put_pixel_safe(img, center_x - y, center_y + x, color);
		mlxlib_put_pixel_safe(img, center_x + y, center_y - x, color);
		mlxlib_put_pixel_safe(img, center_x - y, center_y - x, color);
		
		if (decision <= 0)
		{
			decision = decision + 4 * x + 6;
		}
		else
		{
			decision = decision + 4 * (x - y) + 10;
			y--;
		}
		x++;
	}
}

static void draw_horizontal_line(t_data_img *img, int x1, int x2, int y, int color)
{
	int start, end, i;
	
	if (x1 > x2)
	{
		start = x2;
		end = x1;
	}
	else
	{
		start = x1;
		end = x2;
	}
	
	for (i = start; i <= end; i++)
		mlxlib_put_pixel_safe(img, i, y, color);
}

void mlxlib_fill_circle(t_data_img *img, int center_x, int center_y, int radius, int color)
{
	int x, y, decision;
	
	if (!img || radius <= 0)
		return;
	
	x = 0;
	y = radius;
	decision = 3 - 2 * radius;
	
	while (x <= y)
	{
		/* Draw horizontal lines to fill the circle */
		draw_horizontal_line(img, center_x - x, center_x + x, center_y + y, color);
		draw_horizontal_line(img, center_x - x, center_x + x, center_y - y, color);
		draw_horizontal_line(img, center_x - y, center_x + y, center_y + x, color);
		draw_horizontal_line(img, center_x - y, center_x + y, center_y - x, color);
		
		if (decision <= 0)
		{
			decision = decision + 4 * x + 6;
		}
		else
		{
			decision = decision + 4 * (x - y) + 10;
			y--;
		}
		x++;
	}
}

/* ========== GRADIENT SHAPES ========== */

void mlxlib_draw_gradient_rectangle(t_data_img *img, int x, int y, int width, int height, t_gradient *grad, int direction)
{
	int i, j;
	float position;
	int color;
	
	if (!img || !grad || width <= 0 || height <= 0)
		return;
	
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (direction == 0) /* Horizontal gradient */
				position = (float)j / (width - 1);
			else /* Vertical gradient */
				position = (float)i / (height - 1);
			
			color = mlxlib_gradient_color(grad, position);
			mlxlib_put_pixel_safe(img, x + j, y + i, color);
		}
	}
}

void mlxlib_draw_gradient_circle(t_data_img *img, int center_x, int center_y, int radius, t_gradient *grad)
{
	int x, y;
	float distance, position;
	int color;
	
	if (!img || !grad || radius <= 0)
		return;
	
	/* Draw a radial gradient */
	for (y = center_y - radius; y <= center_y + radius; y++)
	{
		for (x = center_x - radius; x <= center_x + radius; x++)
		{
			distance = sqrtf((x - center_x) * (x - center_x) + (y - center_y) * (y - center_y));
			
			if (distance <= radius)
			{
				position = distance / radius;
				color = mlxlib_gradient_color(grad, position);
				mlxlib_put_pixel_safe(img, x, y, color);
			}
		}
	}
}