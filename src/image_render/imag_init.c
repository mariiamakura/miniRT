/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imag_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:39:27 by mparasku          #+#    #+#             */
/*   Updated: 2023/09/27 14:15:18 by mparasku         ###   ########.fr       */
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

float ft_dot(t_xyz vec1, t_xyz vec2)
{

	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
	 
}

void draw_ball(t_rt **rt) {
    t_objects *cur = (*rt)->scene->objs;
    t_color colors;
    
    ft_init_canva(rt);
    cur->fig.sp.r = cur->fig.sp.r * (*rt)->scene->canva.scale * (*rt)->scene->canva.depth_scale;
    
    // Light source coordinates
    float light_x = (*rt)->scene->light.coord.x;
    float light_y = (*rt)->scene->light.coord.y;
    float light_z = (*rt)->scene->light.coord.z;
    
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            float distance = sqrt((i - (*rt)->scene->canva.x) * (i - (*rt)->scene->canva.x) + (j - (*rt)->scene->canva.y) * (j - (*rt)->scene->canva.y));
            float adjusted_distance = distance / (*rt)->scene->canva.depth_scale;
            
            if (adjusted_distance <= cur->fig.sp.r) {
                // Calculate the direction vector from pixel to light source
                float dir_x = light_x - (i - (*rt)->scene->canva.x);
                float dir_y = light_y - (j - (*rt)->scene->canva.y);
                float dir_z = light_z - cur->fig.sp.coord.z;
                
                // Normalize the direction vector
                float dir_length = sqrt(dir_x * dir_x + dir_y * dir_y + dir_z * dir_z);
                dir_x /= dir_length;
                dir_y /= dir_length;
                dir_z /= dir_length;

				//printf("dir_x: %f, dir_y: %f, dir_z: %f\n", dir_x, dir_y, dir_z);
                
                // Calculate the normal vector for the point on the sphere's surface
                float R = cur->fig.sp.r; // Sphere radius
                float normal_x = (i - (*rt)->scene->canva.x) / R;
                float normal_y = (j - (*rt)->scene->canva.y) / R;
                float normal_z = cur->fig.sp.coord.z / R;
				
                // Normalize the normal vector
                float normal_length = sqrt(normal_x * normal_x + normal_y * normal_y + normal_z * normal_z);
                normal_x /= normal_length;
                normal_y /= normal_length;
                normal_z /= normal_length;

				//printf("normal_x: %f, normal_y: %f, normal_z: %f\n", normal_x, normal_y, normal_z);
                
                // Calculate the dot product between surface normal and light direction
                float dot_product = dir_x * normal_x + dir_y * normal_y + dir_z * normal_z;
                //dot_product = fmaxf(dot_product, 64); if uncomment then the shere is white
                

				printf("dot_product: %f\n", dot_product);

                // Phong shading components
                float ambient = (*rt)->scene->canva.amb_intensity;
                float diffuse = dot_product;
                float specular = powf(dot_product, 0); // Shininess factor (adjust as needed)
                
                // Calculate the final color
                colors.r = cur->fig.sp.color.r * diffuse + ambient;
                colors.g = cur->fig.sp.color.g * diffuse + ambient;
                colors.b = cur->fig.sp.color.b * diffuse + ambient;
                
                // Apply specular highlight (optional)
                colors.r += specular;
                colors.g += specular;
                colors.b += specular;
                
                // Clamp color values
                colors.r = fminf(fmaxf(colors.r, 0), 255);
                colors.g = fminf(fmaxf(colors.g, 0), 255);
                colors.b = fminf(fmaxf(colors.b, 0), 255);
                
                mlx_put_pixel((*rt)->window->img, i, j, ft_pixel(colors.r, colors.g, colors.b, 255)); // Use 255 for alpha (fully opaque)
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
