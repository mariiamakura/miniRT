/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   'TraceRay.c'                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaron  <lbaron@student.42berlin.de>       :+:  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023-10-05 15:19:24 by lbaron            :+:    #+#             */
/*   Updated: 2023-10-05 15:19:24 by lbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

static void	init_trace(t_tra_ray *var, t_rt **rt, t_xyz *O, t_xyz *D)
{
	var->param.o = O;
	var->param.d = D;
	var->param.t_min = 1;
	var->closest_t = FLT_MAX;
	var->closest_object = NULL;
	var->closest_t = closest_inter(rt, var->param, &var->closest_object);
}

t_color	final_collor(t_tra_ray *var, t_rt **rt, t_xyz *O, t_xyz *D)
{
	var->p = ft_get_intersec(O, var->closest_t, D);
	if (var->closest_object->type == SPHERE)
	{
		var->n = ft_xyz_minus(&var->p, &var->closest_object->fig.sp.coord);
		var->n = ft_xyz_normalize(&var->n);
		var->color = var->closest_object->fig.sp.color;
	}
	if (var->closest_object->type == PLANE)
	{
		var->n = var->closest_object->fig.pl.vector;
		var->n = ft_xyz_normalize(&var->n);
		var->color = var->closest_object->fig.pl.color;
	}
	if (var->closest_object->type == CYLINDER)
	{
		var->cylinder = &var->closest_object->fig.cy;
		var->n = ft_xyz_minus(&var->p, &var->closest_object->fig.cy.coord);
		var->n = ft_xyz_normalize(&var->n);
		var->color = var->cylinder->color;
	}
	var->min_d = ft_xyz_unary_minus(D);
	var->i = compute_lighting(&var->p, &var->n, rt, &var->min_d);
	var->fin_color = ft_set_fin_color(&var->color, var->i);
	return (var->fin_color);
}

t_color	trace_ray(t_rt **rt, t_xyz *O, t_xyz *D)
{
	t_tra_ray	var;

	init_trace(&var, rt, O, D);
	if (var.closest_object == NULL)
		return ((t_color){0, 0, 0});
	else
	{
		return (final_collor(&var, rt, O, D));
	}
}
