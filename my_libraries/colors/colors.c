int	clr_create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	clr_get_t(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

int	clr_get_r(int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

int	clr_get_g(int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

int	clr_get_b(int trgb)
{
	return (trgb & 0xFF);
}

/* Enhanced color functions */
int	clr_create_rgb(int r, int g, int b)
{
	return (clr_create_trgb(0, r, g, b));
}

int	clr_add_transparency(int rgb, int transparency)
{
	int r, g, b;
	
	r = clr_get_r(rgb);
	g = clr_get_g(rgb);
	b = clr_get_b(rgb);
	
	if (transparency < 0) transparency = 0;
	if (transparency > 255) transparency = 255;
	
	return (clr_create_trgb(transparency, r, g, b));
}

int	clr_blend(int color1, int color2, float ratio)
{
	int r1, g1, b1, r2, g2, b2;
	int r, g, b;
	
	if (ratio < 0.0f) ratio = 0.0f;
	if (ratio > 1.0f) ratio = 1.0f;
	
	r1 = clr_get_r(color1);
	g1 = clr_get_g(color1);
	b1 = clr_get_b(color1);
	
	r2 = clr_get_r(color2);
	g2 = clr_get_g(color2);
	b2 = clr_get_b(color2);
	
	r = r1 + (int)((r2 - r1) * ratio);
	g = g1 + (int)((g2 - g1) * ratio);
	b = b1 + (int)((b2 - b1) * ratio);
	
	return (clr_create_rgb(r, g, b));
}

int	clr_invert(int color)
{
	int r, g, b;
	
	r = 255 - clr_get_r(color);
	g = 255 - clr_get_g(color);
	b = 255 - clr_get_b(color);
	
	return (clr_create_rgb(r, g, b));
}

int	clr_grayscale(int color)
{
	int r, g, b, gray;
	
	r = clr_get_r(color);
	g = clr_get_g(color);
	b = clr_get_b(color);
	
	/* Using luminance formula */
	gray = (int)(0.299f * r + 0.587f * g + 0.114f * b);
	
	return (clr_create_rgb(gray, gray, gray));
}

int	clr_adjust_brightness(int color, float factor)
{
	int r, g, b;
	
	r = clr_get_r(color);
	g = clr_get_g(color);
	b = clr_get_b(color);
	
	r = (int)(r * factor);
	g = (int)(g * factor);
	b = (int)(b * factor);
	
	if (r > 255) r = 255;
	if (g > 255) g = 255;
	if (b > 255) b = 255;
	if (r < 0) r = 0;
	if (g < 0) g = 0;
	if (b < 0) b = 0;
	
	return (clr_create_rgb(r, g, b));
}
