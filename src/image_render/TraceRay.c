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

t_color TraceRay(t_rt **rt, t_xyz *O, t_xyz *D) {
	float closest_t = FLT_MAX;
	t_objects *closest_object = NULL;

	closest_t = ClosestIntersection(rt, O, D, &closest_object, 1);

	if (closest_object == NULL) {
		return (t_color) {0, 0, 0};
	} else {
		t_xyz P = ft_get_intersec(O, closest_t, D);
		t_xyz N;
		t_color color;
		if (closest_object->type == SPHERE) {
			N = ft_xyz_minus(&P, &closest_object->fig.sp.coord);
			N = ft_xyz_normalize(&N);
			color = closest_object->fig.sp.color;
		}
		else if (closest_object->type == PLANE) {
			N = closest_object->fig.pl.vector;
			N = ft_xyz_normalize(&N);
			color = closest_object->fig.pl.color;
		}
		else if (closest_object->type == CYLINDER) {
			t_cylinder *cylinder = &closest_object->fig.cy;
			t_xyz temp = ft_xyz_mul_num(&cylinder->vector, ft_xyz_dot(&N, &cylinder->vector));
			N.x = N.x - temp.x;
			N.y = N.y - temp.y;
			N.z = N.z - temp.z;
			N = ft_xyz_normalize(&N);
			color = cylinder->color;
		}
		t_xyz min_D = ft_xyz_unary_minus(D);
		float i = ComputeLighting(&P, &N, rt, &min_D);
		t_color fin_color = ft_set_fin_color(&color, i);
		return fin_color;
	}
}