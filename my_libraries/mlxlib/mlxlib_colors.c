#include "mlxlib.h"
#include <math.h>

/* ========== GRADIENT FUNCTIONS ========== */

t_gradient *mlxlib_create_gradient(int start_color, int end_color, int steps)
{
	t_gradient *grad;
	
	if (steps <= 0)
		return (NULL);
	
	grad = malloc(sizeof(t_gradient));
	if (!grad)
		return (NULL);
	
	grad->start_color = start_color;
	grad->end_color = end_color;
	grad->steps = steps;
	
	return (grad);
}

void mlxlib_destroy_gradient(t_gradient *grad)
{
	if (grad)
		free(grad);
}

int mlxlib_gradient_color(t_gradient *grad, float position)
{
	int start_r, start_g, start_b;
	int end_r, end_g, end_b;
	
	if (!grad || position < 0.0f || position > 1.0f)
		return (0);
	
	/* Extract RGB components from start color */
	start_r = clr_get_r(grad->start_color);
	start_g = clr_get_g(grad->start_color);
	start_b = clr_get_b(grad->start_color);
	
	/* Extract RGB components from end color */
	end_r = clr_get_r(grad->end_color);
	end_g = clr_get_g(grad->end_color);
	end_b = clr_get_b(grad->end_color);
	
	/* Interpolate */
	return (mlxlib_interpolate_rgb(start_r, start_g, start_b, end_r, end_g, end_b, position));
}

/* ========== COLOR BLENDING ========== */

int mlxlib_blend_colors(int color1, int color2, float ratio)
{
	int r1, g1, b1;
	int r2, g2, b2;
	
	if (ratio < 0.0f)
		ratio = 0.0f;
	if (ratio > 1.0f)
		ratio = 1.0f;
	
	/* Extract RGB components */
	r1 = clr_get_r(color1);
	g1 = clr_get_g(color1);
	b1 = clr_get_b(color1);
	
	r2 = clr_get_r(color2);
	g2 = clr_get_g(color2);
	b2 = clr_get_b(color2);
	
	return (mlxlib_interpolate_rgb(r1, g1, b1, r2, g2, b2, ratio));
}

int mlxlib_interpolate_rgb(int start_r, int start_g, int start_b, 
			   int end_r, int end_g, int end_b, float ratio)
{
	int r, g, b;
	
	if (ratio < 0.0f)
		ratio = 0.0f;
	if (ratio > 1.0f)
		ratio = 1.0f;
	
	r = start_r + (int)((end_r - start_r) * ratio);
	g = start_g + (int)((end_g - start_g) * ratio);
	b = start_b + (int)((end_b - start_b) * ratio);
	
	/* Ensure values are in valid range */
	if (r < 0) r = 0;
	if (r > 255) r = 255;
	if (g < 0) g = 0;
	if (g > 255) g = 255;
	if (b < 0) b = 0;
	if (b > 255) b = 255;
	
	return (clr_create_trgb(0, r, g, b));
}

/* ========== HSV COLOR SPACE ========== */

int mlxlib_hsv_to_rgb(float h, float s, float v)
{
	float c, x, m;
	float r_prime, g_prime, b_prime;
	int r, g, b;
	
	/* Normalize hue to [0, 360) */
	while (h >= 360.0f) h -= 360.0f;
	while (h < 0.0f) h += 360.0f;
	
	/* Clamp saturation and value */
	if (s < 0.0f) s = 0.0f;
	if (s > 1.0f) s = 1.0f;
	if (v < 0.0f) v = 0.0f;
	if (v > 1.0f) v = 1.0f;
	
	c = v * s;
	x = c * (1.0f - fabsf(fmodf(h / 60.0f, 2.0f) - 1.0f));
	m = v - c;
	
	if (h < 60.0f)
	{
		r_prime = c; g_prime = x; b_prime = 0.0f;
	}
	else if (h < 120.0f)
	{
		r_prime = x; g_prime = c; b_prime = 0.0f;
	}
	else if (h < 180.0f)
	{
		r_prime = 0.0f; g_prime = c; b_prime = x;
	}
	else if (h < 240.0f)
	{
		r_prime = 0.0f; g_prime = x; b_prime = c;
	}
	else if (h < 300.0f)
	{
		r_prime = x; g_prime = 0.0f; b_prime = c;
	}
	else
	{
		r_prime = c; g_prime = 0.0f; b_prime = x;
	}
	
	r = (int)((r_prime + m) * 255.0f);
	g = (int)((g_prime + m) * 255.0f);
	b = (int)((b_prime + m) * 255.0f);
	
	return (clr_create_trgb(0, r, g, b));
}

void mlxlib_rgb_to_hsv(int rgb, float *h, float *s, float *v)
{
	float r, g, b;
	float max_val, min_val, delta;
	
	r = clr_get_r(rgb) / 255.0f;
	g = clr_get_g(rgb) / 255.0f;
	b = clr_get_b(rgb) / 255.0f;
	
	max_val = fmaxf(r, fmaxf(g, b));
	min_val = fminf(r, fminf(g, b));
	delta = max_val - min_val;
	
	/* Value */
	*v = max_val;
	
	/* Saturation */
	if (max_val == 0.0f)
		*s = 0.0f;
	else
		*s = delta / max_val;
	
	/* Hue */
	if (delta == 0.0f)
		*h = 0.0f;
	else if (max_val == r)
		*h = 60.0f * fmodf((g - b) / delta, 6.0f);
	else if (max_val == g)
		*h = 60.0f * ((b - r) / delta + 2.0f);
	else
		*h = 60.0f * ((r - g) / delta + 4.0f);
	
	if (*h < 0.0f)
		*h += 360.0f;
}

/* ========== COLOR UTILITIES ========== */

int mlxlib_lighten_color(int color, float factor)
{
	float h, s, v;
	
	if (factor < 0.0f)
		factor = 0.0f;
	
	mlxlib_rgb_to_hsv(color, &h, &s, &v);
	v = fminf(1.0f, v + factor);
	
	return (mlxlib_hsv_to_rgb(h, s, v));
}

int mlxlib_darken_color(int color, float factor)
{
	float h, s, v;
	
	if (factor < 0.0f)
		factor = 0.0f;
	
	mlxlib_rgb_to_hsv(color, &h, &s, &v);
	v = fmaxf(0.0f, v - factor);
	
	return (mlxlib_hsv_to_rgb(h, s, v));
}