/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imag_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:39:27 by mparasku          #+#    #+#             */
/*   Updated: 2023/09/25 15:28:34 by mparasku         ###   ########.fr       */
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
	int radius;

	center.x = WIDTH / 2 + cur->fig.sp.coord.x * 10;
	center.y = HEIGHT / 2 + cur->fig.sp.coord.y * 10;
	float depth_scale = 1.0 + cur->fig.sp.coord.z / 100;
	radius = cur->fig.sp.r * 10 * depth_scale;

	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			float distance = sqrt((i - center.x) * (i - center.x) + (j - center.y) * (j - center.y));
			float adjusted_distance = distance / depth_scale;
			if (adjusted_distance <= radius)
			{
				mlx_put_pixel(rt->window->img, i, j, ft_pixel(cur->fig.sp.color.r, cur->fig.sp.color.g, cur->fig.sp.color.b, 255));
			}
		}
	}
}

void ft_randomize(void* param)
{
	t_rt *rt;

	rt = (t_rt*)param;
	for (uint32_t i = 0; i < rt->window->img->width; ++i)
	{
		for (uint32_t y = 0; y < rt->window->img->height; ++y)
		{
			uint32_t color = ft_pixel(
					rand() % 0xFF, // R
					rand() % 0xFF, // G
					rand() % 0xFF, // B
					rand() % 0xFF  // A
			);
			mlx_put_pixel(rt->window->img, i, y, color);
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
//	mlx_loop_hook((*rt)->window->mlx, ft_randomize, (*rt));
	mlx_loop_hook((*rt)->window->mlx, ft_hook, (*rt));
	draw_ball(*rt);
	//mlx_key_hook((*rt)->window->mlx, ft_key_callback, (*rt));
	mlx_loop((*rt)->window->mlx);
	return (TRUE);
}

void ft_key_callback(mlx_key_data_t key_data, void *rt)
{
	t_rt *new_rt;
	new_rt = (t_rt *)rt;

	if (key_data.action == MLX_PRESS && key_data.key == MLX_KEY_ESCAPE)
		mlx_close_window(new_rt->window->mlx);
}