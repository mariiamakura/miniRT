/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   'IntersectRay.c'                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaron  <lbaron@student.42berlin.de>       :+:  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023-10-05 14:48:34 by lbaron            :+:    #+#             */
/*   Updated: 2023-10-05 14:48:34 by lbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	intersect_ray_sp(t_int param, t_sphere *sp, float *t1, float *t2)
{
	t_xyz	*c;
	float	r;
	t_xyz	oc;
	t_ks	ks;
	float	discriminant;

	c = &sp->coord;
	r = sp->r;
	oc = ft_xyz_minus(param.o, c);
	ks.k1 = ft_xyz_dot(param.d, param.d);
	ks.k2 = 2 * ft_xyz_dot(&oc, param.d);
	ks.k3 = ft_xyz_dot(&oc, &oc) - r * r;
	discriminant = ks.k2 * ks.k2 - 4 * ks.k1 * ks.k3;
	if (discriminant < 0)
	{
		return (FALSE);
	}
	*t1 = (-ks.k2 + sqrt(discriminant)) / (2 * ks.k1);
	*t2 = (-ks.k2 - sqrt(discriminant)) / (2 * ks.k1);
	return (TRUE);
}

int	intersect_ray_pl(t_int param, t_plane *pl, float *t)
{
	t_xyz	normal;
	t_xyz	oc;
	float	denominator;

	normal = pl->vector;
	denominator = ft_xyz_dot(param.d, &normal);
	if (fabs(denominator) < 0.0001f)
	{
		return (FALSE);
	}
	oc = ft_xyz_minus(param.o, &pl->coord);
	*t = -ft_xyz_dot(&oc, &normal) / denominator;
	if (*t < 0.0f)
	{
		return (FALSE);
	}
	return (TRUE);
}

t_xyz	reveal_intersectionpoint_xyz(t_int param, float t)
{
	t_xyz	dir;
	t_xyz	inter;

	dir = ft_xyz_mul_num(param.d, t);
	inter = ft_xyz_plus(param.o, &dir);
	return (inter);
}

float	ft_distance(t_xyz *vec1, t_xyz *vec2)
{
	float	distance;
	t_xyz	diff;

	diff = ft_xyz_minus(vec1, vec2);
	distance = ft_xyz_length(&diff);
	return (distance);
}

int	in_one_cap_cy(t_int param, t_cylinder *cy, t_plane *pl, float *t)
{
	float	distance;
	t_xyz	inter;

	if (!intersect_ray_pl(param, pl, t))
		return (FALSE);
	inter = reveal_intersectionpoint_xyz(param, *t);
	distance = ft_distance(&inter, &pl->coord);
	if (distance > cy->diameter / 2.0f)
		return (FALSE);
	return (TRUE);
}
