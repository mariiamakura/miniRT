/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imag_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:39:27 by mparasku          #+#    #+#             */
/*   Updated: 2023/09/28 14:22:30 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

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

void ft_set_colors(t_color *result_color, float normalized_distance, t_color base_color)
{
	result_color->r = normalized_distance * base_color.r;
	result_color->g = normalized_distance * base_color.g;
	result_color->b = normalized_distance * base_color.b;

	result_color->r = fminf(fmaxf(result_color->r, 0), 255);
	result_color->g = fminf(fmaxf(result_color->g, 0), 255);
	result_color->b = fminf(fmaxf(result_color->b, 0), 255);
}

float ft_dot(t_xyz *vec1, t_xyz *vec2)
{

	return (vec1->x * vec2->x + vec1->y * vec2->y + vec1->z * vec2->z);
	 
}

void ft_normalize(t_xyz *ray)
{
	float length;
	
	length = sqrt(ft_dot(ray, ray));
	ray->x /= length;
	ray->y /= length;
	ray->z /= length;
	
}

void ft_set_light_dir(t_xyz *light_dir, t_rt **rt)
{
	t_light light;
	t_camera camera;
	
	light = (*rt)->scene->light;
	camera = (*rt)->scene->camera;
	
	light_dir->x = light.coord.x - camera.coord.x;
	light_dir->y = light.coord.y - camera.coord.y;
	light_dir->z = light.coord.z - camera.coord.z;
}

void draw_ball(t_rt **rt) {

	t_xyz light_dir;
	t_xyz intersection;
	t_color colors;
	t_xyz cam_vec;
	t_sphere sp;
	t_xyz cam_ori;
	t_xyz sp_norm;

	sp = (*rt)->scene->objs->fig.sp;
	cam_ori = (*rt)->scene->camera.coord;

	ft_set_light_dir(&light_dir, rt);
	ft_normalize(&light_dir);
	//printf("x %f y %f z %f\n", light_dir.x, light_dir.y, light_dir.z);
	for (int pix_x = 0; pix_x < WIDTH; pix_x++) {
		for (int pix_y = 0; pix_y < HEIGHT; pix_y++) {

			cam_vec.x = cam_ori.x - sp.coord.x;
			cam_vec.y = cam_ori.y - sp.coord.y;
			cam_vec.z = cam_ori.z - sp.coord.z;
			ft_normalize(&cam_vec);
			
			float a = ft_dot(&light_dir, &light_dir);
			float b = 2 * ft_dot(&light_dir, &cam_vec);
			float c = ft_dot(&cam_vec, &cam_vec) - (sp.r * sp.r);
			
			float discr = b * b - 4 * a * c;
			printf("%f\n", discr);

			if (discr >= 0)
			{
				float t1 = (-b + sqrt(discr)) / (2 * a);
				float t2 = (-b - sqrt(discr)) / (2 * a);

				float t = fmin(t1, t2);

				intersection.x = cam_ori.x + t * (float)pix_x;
				intersection.y = cam_ori.y + t * (float)pix_y;
				intersection.z = cam_ori.z + t * 1;

				sp_norm.x = intersection.x - sp.coord.x; 
				sp_norm.y = intersection.y - sp.coord.y; 
				sp_norm.z = intersection.z - sp.coord.z; 
				ft_normalize(&sp_norm);

				float diffuse = fmax(ft_dot(&sp_norm, &light_dir), 0.0);
			
				colors.r = diffuse * sp.color.r;
				colors.g = diffuse * sp.color.g;
				colors.b = diffuse * sp.color.b;

				colors.r = fmin(255.0, fmax(0.0, colors.r));
				colors.g = fmin(255.0, fmax(0.0, colors.g));
				colors.b = fmin(255.0, fmax(0.0, colors.b));

				mlx_put_pixel((*rt)->window->img, pix_x, pix_y, ft_pixel(colors.r, colors.g, colors.b, 255)); // Use 255 for alpha (fully opaque)
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
