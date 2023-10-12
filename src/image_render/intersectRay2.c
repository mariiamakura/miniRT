/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   'intersectRay2.c'                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaron  <lbaron@student.42berlin.de>       :+:  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023-10-12 16:50:27 by lbaron            :+:    #+#             */
/*   Updated: 2023-10-12 16:50:27 by lbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	intersect_ray_caps_cy(t_int param, t_cylinder *cylinder, float *t)
{
	t_ray_caps	var;

	var.half_h = cylinder->height / 2.0f;
	var.norm = ft_xyz_normalize(&cylinder->vector);
	var.half_h_norm = ft_xyz_mul_num(&var.norm, var.half_h);
	var.top.vector = var.norm;
	var.bottom.vector = ft_xyz_unary_minus(&var.norm);
	var.top.coord = ft_xyz_plus(&cylinder->coord, &var.half_h_norm);
	var.bottom.coord = ft_xyz_minus(&cylinder->coord, &var.half_h_norm);
	var.top_intersected = in_one_cap_cy(param, cylinder, &var.top, &var.t_top);
	var.bottom_intersected = in_one_cap_cy(param, cylinder,
			&var.bottom, &var.t_bottom);
	if (!var.top_intersected && !var.bottom_intersected)
		return (FALSE);
	if (!var.bottom_intersected)
		*t = var.t_top;
	else if (!var.top_intersected)
		*t = var.t_bottom;
	else
		*t = fminf(var.t_top, var.t_bottom);
	return (TRUE);
}

int	intersect_ray_side(t_int param, t_cylinder *cylinder, float *t1)
{
	t_rays	var;

	var.cb = cylinder->coord;
	var.v = cylinder->vector;
	var.r = cylinder->diameter / 2.0f;
	var.h = cylinder->height / 2.0f;
	var.r_surrounding_sphere = sqrtf(var.r * var.r + var.h * var.h);
	var.oc = ft_xyz_minus(param.o, &var.cb);
	var.a = ft_xyz_dot(param.d, param.d)
		- ft_xyz_dot(param.d, &var.v) * ft_xyz_dot(param.d, &var.v);
	var.b = 2.0f * (ft_xyz_dot(param.d, &var.oc)
			- ft_xyz_dot(param.d, &var.v) * ft_xyz_dot(&var.oc, &var.v));
	var.c = ft_xyz_dot(&var.oc, &var.oc) - ft_xyz_dot(&var.oc, &var.v)
		* ft_xyz_dot(&var.oc, &var.v) - var.r * var.r;
	var.discriminant = var.b * var.b - 4.0f * var.a * var.c;
	if (var.discriminant < 0.0f)
		return (FALSE);
	var.t0_ = (-var.b - sqrtf(var.discriminant)) / (2.0f * var.a);
	var.t1_ = (-var.b + sqrtf(var.discriminant)) / (2.0f * var.a);
	*t1 = fminf(var.t0_, var.t1_);
	var.point = reveal_intersectionpoint_xyz(param, *t1);
	var.distance = ft_distance(&var.point, &cylinder->coord);
	if (var.distance > var.r_surrounding_sphere)
		return (FALSE);
	return (TRUE);
}

int	intersect_ray_cy(t_int param, t_cylinder *cy, float *t)
{
	float	t_top;
	float	t_bottom;
	int		top_intersected;
	int		bottom_intersected;

	top_intersected = intersect_ray_side(param, cy, &t_top);
	bottom_intersected = intersect_ray_caps_cy(param, cy, &t_bottom);
	if (!top_intersected && !bottom_intersected)
		return (FALSE);
	if (!bottom_intersected)
		*t = t_top;
	else if (!top_intersected)
		*t = t_bottom;
	else
		*t = fminf(t_top, t_bottom);
	return (TRUE);
}
