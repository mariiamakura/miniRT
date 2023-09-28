#include "../../include/miniRT.h"

void ft_gradient(t_color *color, t_rt **rt)
{
	for (int x = 0; x < WIDTH; x++) {
		for (int y = 0; y < HEIGHT; y++) {
			//printf("Scanlines remaining: %i\n", HEIGHT - y);
			float r = (float)x / (WIDTH - 1);
			float g = 0;
			float b = (float)y / (HEIGHT - 1);

			int ir = (int)(color->r * r);
			int ig = (int)(color->g * g);
			int ib = (int)(color->b * b);

			 mlx_put_pixel((*rt)->window->img, x, y, ft_pixel(ir, ig, ib, 255)); 

		}
	}
}

void ft_put_pixel(int x, int y, int color, t_rt **rt)
{
	int can_x;
	int can_y;

	can_x = x + WIDTH / 2;
	can_y = y + HEIGHT / 2;

	//printf("------rendering %i row-----------", can_y);
	if (can_x >= 0 && can_x < WIDTH && can_y >= 0 && can_y < HEIGHT)
		mlx_put_pixel((*rt)->window->img, can_x, can_y, color); 
}

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

