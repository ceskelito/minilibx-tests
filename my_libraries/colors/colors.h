#ifndef COLORS_H
# define COLORS_H

# include "colorsdef.h"

int	clr_create_trgb(int t, int r, int g, int b);
int	clr_get_t(int trgb);
int	clr_get_r(int trgb);
int	clr_get_g(int trgb);
int	clr_get_b(int trgb);

/* Enhanced color functions for gradients and manipulation */
int	clr_create_rgb(int r, int g, int b);
int	clr_add_transparency(int rgb, int transparency);
int	clr_blend(int color1, int color2, float ratio);
int	clr_invert(int color);
int	clr_grayscale(int color);
int	clr_adjust_brightness(int color, float factor);

#endif
