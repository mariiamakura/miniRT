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

float ClosestIntersection(t_rt **rt, t_xyz *O, t_xyz *D, t_objects **closest_object, float t_min) {
	float closest_t = FLT_MAX;
	t_objects *object = (*rt)->sc->objs;

	while (object != NULL) {
		if (object->type == SPHERE) {
			t_sphere *sphere = &(object->fig.sp);
			float t1, t2;
			if (IntersectRaySphere(O, D, sphere, &t1, &t2)) {
				if (t1 > t_min && t1 < closest_t) {
					closest_t = t1;
					*closest_object = object;
				}
				if (t2 > t_min && t2 < closest_t) {
					closest_t = t2;
					*closest_object = object;
				}
			}
		}
		else if (object->type == PLANE) {
			t_plane *plane = &(object->fig.pl);
			float t;
			if (IntersectRayPlane(O, D, plane, &t) && t > t_min && t < closest_t) {
				closest_t = t;
				*closest_object = object;
			}
		}
		else if (object->type == CYLINDER) {
			t_cylinder *cylinder = &(object->fig.cy);
			float t1, t2;
            //float t1, t2, tCap1, tCap2;

			// Check intersection with the cylinder body
			if (IntersectRayCylinder(O, D, cylinder, &t1, &t2) && ((t1 > t_min && t1 < closest_t) || (t2 > t_min && t2 < closest_t)))
			{
				if (t1 > t_min && t1 < closest_t)
				{
					closest_t = t1;
                    *closest_object = object;
				}
				if (t2 > t_min && t2 < closest_t)
				{
					closest_t = t2;
                    *closest_object = object;
				}
			}

//			// Check intersection with the bottom cap
//			if (IntersectRayCap(O, D, cylinder, &tCap1, FALSE) && tCap1 > t_min && tCap1 < closest_t) {
//				closest_t = tCap1;
//				*closest_object = object;
//			}
//
//			// Check intersection with the top cap
//			if (IntersectRayCap(O, D, cylinder, &tCap2, TRUE) && tCap2 > t_min && tCap2 < closest_t) {
//				closest_t = tCap2;
//				*closest_object = object;
//			}
		}

		object = object->next;
	}

	return closest_t;
}