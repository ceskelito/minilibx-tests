#ifndef COLORS_H
# define COLORS_H

# include "colorsdef.h"

int	clr_create_trgb(int t, int r, int g, int b);
int	clr_get_t(int trgb);
int	clr_get_r(int trgb);
int	clr_get_g(int trgb);
int	clr_get_b(int trgb);

#endif
