/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imag_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:39:27 by mparasku          #+#    #+#             */
/*   Updated: 2023/10/06 18:00:55 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_xyz	ft_can_to_vport(int x, int y, int fov)
{
	float	distance;
	t_xyz	res;

	distance = VW / (2 * tan((float) fov / 2 * M_PI / 180));
	res.x = (float) x * VW / CW;
	res.y = (float) y * VH / CH;
	res.z = distance;
	return (res);
}

t_xyz	ft_get_intersec(t_xyz *O, float closest_t, t_xyz *D)
{
	t_xyz	p;

	p.x = O->x + closest_t * D->x;
	p.y = O->y + closest_t * D->y;
	p.z = O->z + closest_t * D->z;
	return (p);
}

void	ft_hook(void *param)
{
	t_rt	**rt;

	rt = (t_rt **) param;
	ft_process_cam_movement(rt);
	ft_process_cam_rotation(rt);
	render_sc(rt);
}

int	ft_imag_init(t_rt **rt)
{
	(*rt)->window = malloc(sizeof(t_window));
	if (!(*rt)->window)
		return (ft_error("mlx error"));
	(*rt)->window->mlx = mlx_init(CW, CH, "miniRT", true);
	if (!(*rt)->window->mlx)
		return (ft_error("mlx error"));
	(*rt)->window->img = mlx_new_image((*rt)->window->mlx, CW, CH);
	if (!(*rt)->window->img)
	{
		mlx_close_window((*rt)->window->mlx);
		return (ft_error("img error"));
	}
	if (mlx_image_to_window((*rt)->window->mlx, (*rt)->window->img, 0, 0) == -1)
	{
		mlx_close_window((*rt)->window->mlx);
		return (ft_error("img error"));
	}
	mlx_loop_hook((*rt)->window->mlx, ft_hook, rt);
	mlx_loop((*rt)->window->mlx);
	return (TRUE);
}
