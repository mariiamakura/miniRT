/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imag_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:39:27 by mparasku          #+#    #+#             */
/*   Updated: 2023/09/26 15:22:10 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}


/* typedef struct s_canva
{
	int x;
	int y;
	int amb_intensity;
	float depth_scale; 
} t_canva;
 */

void ft_init_canva(t_rt **rt)
{
	t_canva n_canva;
	t_sphere sp;

	sp = (*rt)->scene->objs->fig.sp;
	n_canva.scale = 10;
	n_canva.x = WIDTH / 2 + sp.coord.x * n_canva.scale;
	n_canva.y = HEIGHT / 2 + sp.coord.y * n_canva.scale * -1;
	n_canva.amb_intensity = (*rt)->scene->ambient.ratio * 255;
	n_canva.depth_scale = ((*rt)->scene->camera.fov / 90) + sp.coord.z / 100;

	(*rt)->scene->canva = n_canva;
}

t_color ft_set_colors(int norm_dist, t_color orig_colors)
{
	t_color colors;

	colors.r = norm_dist * orig_colors.r;
	colors.g = norm_dist * orig_colors.g;
	colors.b = norm_dist * orig_colors.b;

	colors.r = fminf(fmaxf(colors.r, 0), 255);
	colors.g = fminf(fmaxf(colors.g, 0), 255);
	colors.b = fminf(fmaxf(colors.b, 0), 255);

	return (colors);
}

void draw_ball(t_rt **rt) //here we need only scene, then maybe we pass only scene?
{
	t_objects *cur = (*rt)->scene->objs;
	t_color colors;
	
	ft_init_canva(rt);
	cur->fig.sp.r = cur->fig.sp.r * (*rt)->scene->canva.scale * (*rt)->scene->canva.depth_scale;

	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			float distance = sqrt((i - (*rt)->scene->canva.x) * (i - (*rt)->scene->canva.x) + (j - (*rt)->scene->canva.y) * (j - (*rt)->scene->canva.y));
			float adjusted_distance = distance / (*rt)->scene->canva.depth_scale;
			float normalized_distance = 1.0 - (adjusted_distance / cur->fig.sp.r);
			//colors = ft_set_colors(normalized_distance, cur->fig.sp.color); //doesnt work why?
			colors.r = normalized_distance * cur->fig.sp.color.r;
			colors.g = normalized_distance * cur->fig.sp.color.g;
			colors.b = normalized_distance * cur->fig.sp.color.b;

			colors.r = fminf(fmaxf(colors.r, 0), 255);
			colors.g = fminf(fmaxf(colors.g, 0), 255);
			colors.b = fminf(fmaxf(colors.b, 0), 255);

			if (adjusted_distance <= cur->fig.sp.r)
			{
				mlx_put_pixel((*rt)->window->img, i, j, ft_pixel(colors.r, colors.g, colors.b, (*rt)->scene->canva.amb_intensity)); //the 4 value behaves like amb light
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
	draw_ball(rt);
	//mlx_key_hook((*rt)->window->mlx, ft_key_callback, (*rt));
	mlx_loop((*rt)->window->mlx);
	return (TRUE);
}
