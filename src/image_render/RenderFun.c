/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   'RenderFun.c'                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaron  <lbaron@student.42berlin.de>       :+:  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023-10-12 17:09:54 by lbaron            :+:    #+#             */
/*   Updated: 2023-10-12 17:09:54 by lbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	ft_render_fun(t_rt **rt, int Cx, int Cy)
{
	t_xyz			o;
	t_matrix_3x3	rot;
	t_xyz			can_to_v;
	t_xyz			d;
	t_color			color;

	o = (*rt)->sc->cam.coord;
	rot = (*rt)->sc->cam.rot;
	can_to_v = ft_can_to_vport(Cx, Cy, (*rt)->sc->cam.fov);
	d = ft_mat_mul_xyz(&rot, &can_to_v);
	color = trace_ray(rt, &o, &d);
	return (ft_pixel(color.r, color.g, color.b, 255));
}

void	render_sc(t_rt **rt)
{
	int	sx;
	int	sy;
	int	cx;
	int	cy;
	int	fin_color;

	sx = 0;
	while (sx < CW)
	{
		sy = 0;
		while (sy < CH)
		{
			cx = sx - CW / 2;
			cy = CH / 2 - sy;
			fin_color = ft_render_fun(rt, cx, cy);
			mlx_put_pixel((*rt)->window->img, sx, sy, fin_color);
			sy++;
		}
		sx++;
	}
}
