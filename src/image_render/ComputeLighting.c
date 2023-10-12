/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   'ComputeLighting.c'                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaron  <lbaron@student.42berlin.de>       :+:  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023-10-12 17:07:54 by lbaron            :+:    #+#             */
/*   Updated: 2023-10-12 17:07:54 by lbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

static void	init_cp_light(t_cpt_light	*var, t_rt **rt)
{
	var->amb = (*rt)->sc->ambient;
	var->light_point = (*rt)->sc->light;
	var->i = 0.0;
	var->s = 150;
	var->shadow_object = NULL;
	var->param.t_min = 0.001;
	if (var->amb.ratio == 0.0)
		var->i = 0.1;
	else if (var->amb.ratio == 1.0)
		var->i = 0.9;
	else
		var->i += var->amb.ratio;
}

float	compute_lighting(t_xyz *P, t_xyz *N, t_rt **rt, t_xyz *V)
{
	t_cpt_light	var;

	init_cp_light (&var, rt);
	var.l = ft_xyz_minus(&var.light_point.coord, P);
	var.param.o = P;
	var.param.d = &var.l;
	closest_inter(rt, var.param, &var.shadow_object);
	if (var.shadow_object != NULL)
		return (var.i);
	var.n_dot_l = ft_xyz_dot(N, &var.l);
	if (var.n_dot_l > 0)
		var.i += var.light_point.ratio * var.n_dot_l
			/ (ft_xyz_length(N) * ft_xyz_length(&var.l));
	var.v_2n = ft_xyz_mul_num(N, 2.0);
	var.dot_nl = ft_xyz_dot(N, &var.l);
	var.a = ft_xyz_mul_num(&var.v_2n, var.dot_nl);
	var.r = ft_xyz_minus(&var.a, &var.l);
	var.r_dot_v = ft_xyz_dot(&var.r, V);
	if (var.r_dot_v > 0)
	{
		var.b = var.r_dot_v / (ft_xyz_length(&var.r) * ft_xyz_length(V));
		var.i += var.light_point.ratio * powf(var.b, var.s);
	}
	return (var.i);
}
