/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imag_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:39:27 by mparasku          #+#    #+#             */
/*   Updated: 2023/09/28 16:55:49 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

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

void ft_get_viewpoint(int x, int y, t_xyz *viewPoint/*, t_rt **rt*/)
{
    //float fov_radians = (*rt)->scene->camera.fov * M_PI / 180;
    viewPoint->x = x;
    viewPoint->y = y;
    //viewPoint->z = Cw / (2 * tan(fov_radians / 2));
    viewPoint->z = 1;
}

void ft_intersect(t_xyz *cam_ori, t_xyz *viewPoint, t_sphere *sp, t_hitPoint *hitPoint)
{
    t_xyz cam_min_sp;
    cam_min_sp.x = cam_ori->x - sp->coord.x;
    cam_min_sp.y = cam_ori->y - sp->coord.y;
    cam_min_sp.z = cam_ori->z - sp->coord.z;
//    sp->r = sp->r * 10;
//
//    printf("%f\n", sp->r )

    //printf("shere %f %f %f\n", sp->coord.x, sp->coord.y, sp->coord.z);
    //printf("cam ori %f %f %f\n", cam_ori->x,  cam_ori->y,  cam_ori->z);
    float a = ft_dot(viewPoint, viewPoint);
    float b = 2 * ft_dot(&cam_min_sp, viewPoint);
    float c = ft_dot(&cam_min_sp, &cam_min_sp) - sp->r * sp->r;

    float discr = b * b - 4 * a * c;
    //printf("%f\n", discr);
    if (discr < 0)
    {
        hitPoint->h1 = FLT_MAX;
        hitPoint->h2 = FLT_MAX;
        return ;
    }

    hitPoint->h1 = (-b + sqrt(discr)) / (2 * a);
    hitPoint->h2 = (-b - sqrt(discr)) / (2 * a);
}

int ft_rayTrace(t_xyz *cam_ori, t_xyz *viewPoint, t_rt **rt)
{
    t_hitPoint hitPont;

    float t_min = 1;
    float t_max = FLT_MAX;
    float closest_t = FLT_MAX;
    ft_intersect(cam_ori, viewPoint, &(*rt)->scene->objs->fig.sp, &hitPont);
    //printf("hit point1 %f hit point2 %f\n", hitPont.h1, hitPont.h2);
    if (hitPont.h1 > t_min && hitPont.h1 < t_max && hitPont.h1 < closest_t)
        closest_t = hitPont.h1;
    if (hitPont.h2 > t_min && hitPont.h2 < t_max && hitPont.h2 < closest_t)
        closest_t = hitPont.h2;
    if (closest_t == FLT_MAX)
        return ft_pixel(255, 255, 255, 255);
    return ft_pixel(255, 0, 255, 255);
}


void draw_ball(t_rt **rt)
{
	
	t_xyz cam_ori;
	//t_color colors;
	//int d = 1;
	int fin_color;
    t_xyz viewPoint;

	cam_ori = (*rt)->scene->camera.coord;
	//colors = (*rt)->scene->objs->fig.sp.color;
	for (int x = (Cw / 2 * -1); x < Cw / 2; x++) {
		for (int y = (Ch / 2 * -1); y < Ch / 2; y++) {

            ft_get_viewpoint(x, y, &viewPoint);
            fin_color = ft_rayTrace(&cam_ori, &viewPoint, rt);
            //printf("%f %f %f\n", viewPoint.x, viewPoint.y, viewPoint.z);

		//fin_color = ft_pixel(colors.r, colors.g, colors.b, 255);
		ft_put_pixel(x, y, fin_color, rt);
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
	(*rt)->window->mlx = mlx_init(Cw, Ch, "miniRT", true);
	if (!(*rt)->window->mlx)
		return(ft_error("mlx error"));
	(*rt)->window->img = mlx_new_image((*rt)->window->mlx, Cw, Ch);
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
