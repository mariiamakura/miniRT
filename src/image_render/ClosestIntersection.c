/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   'ClosestIntersection.c'                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaron  <lbaron@student.42berlin.de>       :+:  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023-10-05 15:19:16 by lbaron            :+:    #+#             */
/*   Updated: 2023-10-05 15:19:16 by lbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

static int	process_sphere(t_int param, float *closest_t,
							t_objects **object, t_objects **closest_obj)
{
	t_sphere	*sphere;
	float		t[2];

	sphere = &((*object)->fig.sp);
	if (intersect_ray_sp(param, sphere, &t[0], &t[1]))
	{
		if (t[0] > param.t_min && t[0] < *closest_t)
		{
			*closest_t = t[0];
			*closest_obj = *object;
		}
		if (t[1] > param.t_min && t[1] < *closest_t)
		{
			*closest_t = t[1];
			*closest_obj = *object;
		}
	}
	return (1);
}

static int	process_pl_cy(t_int param, float *closest_t,
							t_objects **object, t_objects **closest_obj)
{
	float	t;

	if ((*object)->type == PLANE
		&& intersect_ray_pl(param, &((*object)->fig.pl), &t)
		&& t > param.t_min && t < *closest_t)
	{
		*closest_t = t;
		*closest_obj = *object;
	}
	else if ((*object)->type == CYLINDER
		&& intersect_ray_cy(param, &((*object)->fig.cy), &t)
		&& t > param.t_min && t < *closest_t)
	{
		*closest_t = t;
		*closest_obj = *object;
	}
	return (1);
}

float	closest_inter(t_rt **rt, t_int param,
			t_objects **closest_obj)
{
	float		closest_t;
	t_objects	*object;

	closest_t = FLT_MAX;
	object = (*rt)->sc->objs;
	while (object)
	{
		if (object->type == SPHERE)
			process_sphere(param, &closest_t, &object, closest_obj);
		else if (object->type == PLANE || object->type == CYLINDER)
			process_pl_cy(param, &closest_t, &object, closest_obj);
		object = object->next;
	}
	return (closest_t);
}
