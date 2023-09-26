/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imag_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:39:27 by mparasku          #+#    #+#             */
/*   Updated: 2023/09/26 14:06:41 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void draw_ball(t_rt *rt)
{
	t_objects *cur = rt->scene->objs;
	t_xyz center;
	t_color colors;
	int radius;
	int scale = 10;

	center.x = WIDTH / 2 + cur->fig.sp.coord.x * scale;
	center.y = HEIGHT / 2 + cur->fig.sp.coord.y * scale * -1;
	int amb_intc =rt->scene->ambient.ratio * 255;
	float depth_scale = (rt->scene->camera.fov / 90) + cur->fig.sp.coord.z / 100; //53C is 1.0 
	radius = cur->fig.sp.r * scale * depth_scale;

	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			float distance = sqrt((i - center.x) * (i - center.x) + (j - center.y) * (j - center.y));
			float adjusted_distance = distance / depth_scale;
			float normalized_distance = 1.0 - (adjusted_distance / radius);
			colors.r = normalized_distance * cur->fig.sp.color.r;
			colors.g = normalized_distance * cur->fig.sp.color.g;
			colors.b = normalized_distance * cur->fig.sp.color.b;

			colors.r = fminf(fmaxf(colors.r, 0), 255);
			colors.g = fminf(fmaxf(colors.g, 0), 255);
			colors.b = fminf(fmaxf(colors.b, 0), 255);

			if (adjusted_distance <= radius)
			{
				mlx_put_pixel(rt->window->img, i, j, ft_pixel(colors.r, colors.g, colors.b, amb_intc)); //the 4 value behaves like amb light
			}
		}
	}
}

void ft_hook(void* param)
{
	t_rt *rt;

	rt = (t_rt*)param;
	if (mlx_is_key_down(rt->window->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(rt->window->mlx);
	if (mlx_is_key_down(rt->window->mlx, MLX_KEY_UP))
		rt->window->img->instances[0].y -= 5;
	if (mlx_is_key_down(rt->window->mlx, MLX_KEY_DOWN))
		rt->window->img->instances[0].y += 5;
	if (mlx_is_key_down(rt->window->mlx, MLX_KEY_LEFT))
		rt->window->img->instances[0].x -= 5;
	if (mlx_is_key_down(rt->window->mlx, MLX_KEY_RIGHT))
		rt->window->img->instances[0].x += 5;
}

int ft_imag_init(t_rt **rt)
{
	(*rt)->window = malloc(sizeof(t_window));
	if (!(*rt)->window)
		return(ft_error("mlx error"));
	(*rt)->window->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!(*rt)->window->mlx)
		return(ft_error("mlx error"));
	(*rt)->window->img = mlx_new_image((*rt)->window->mlx, WIDTH, HEIGHT);
	if (!(*rt)->window->img)
	{
		mlx_close_window((*rt)->window->mlx);
		return(ft_error("img error"));
	}
	if (mlx_image_to_window((*rt)->window->mlx, (*rt)->window->img, 0, 0) == -1)
	{
		mlx_close_window((*rt)->window->mlx);
		return(ft_error("img error"));
	}
	mlx_loop_hook((*rt)->window->mlx, ft_hook, (*rt));
	//ft_camera_orient(rt);
	draw_ball(*rt);
	//mlx_key_hook((*rt)->window->mlx, ft_key_callback, (*rt));
	mlx_loop((*rt)->window->mlx);
	return (TRUE);
}
