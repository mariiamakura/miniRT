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

int IntersectRaySphere(t_xyz *O, t_xyz *D, t_sphere *sphere, float *t1, float *t2) {
	t_xyz *C = &sphere->coord;
	float r = sphere->r;
	t_xyz OC = ft_xyz_minus(O, C);

	float k1 = ft_xyz_dot(D, D);
	float k2 = 2 * ft_xyz_dot(&OC, D);
	float k3 = ft_xyz_dot(&OC, &OC) - r * r;

	float discriminant = k2 * k2 - 4 * k1 * k3;
	if (discriminant < 0) {
		return FALSE;
	}

	*t1 = (-k2 + sqrt(discriminant)) / (2 * k1);
	*t2 = (-k2 - sqrt(discriminant)) / (2 * k1);
	return TRUE;
}

int IntersectRayPlane(t_xyz *O, t_xyz *D, t_plane *plane, float *t) {
	t_xyz normal = plane->vector;
	float denominator = ft_xyz_dot(D, &normal);
	if (fabs(denominator) < 0.0001f) {
		return FALSE;
	}
	t_xyz OC = ft_xyz_minus(O, &plane->coord);
    //printf("%f %f %f\n", OC.x, OC.y, OC.z);
	*t = -ft_xyz_dot(&OC, &normal) / denominator;
	if (*t < 0.0f) {
		return FALSE;
	}
	return TRUE;
}

int IntersectRayCylinder(t_xyz *O, t_xyz *D, t_cylinder *cylinder, float *t1) {
    t_xyz C = cylinder->coord;
    t_xyz V = cylinder->vector;
    float r = cylinder->diameter / 2.0f;
    float h = cylinder->height / 2.0f;

    t_xyz OC = ft_xyz_minus(O, &C);
    float a = ft_xyz_dot(D, D) - ft_xyz_dot(D, &V) * ft_xyz_dot(D, &V);
    float b = 2.0f * (ft_xyz_dot(D, &OC) - ft_xyz_dot(D, &V) * ft_xyz_dot(&OC, &V));
    float c = ft_xyz_dot(&OC, &OC) - ft_xyz_dot(&OC, &V) * ft_xyz_dot(&OC, &V) - r * r;
    float discriminant = b * b - 4.0f * a * c;

    if (discriminant < 0.0f) {

        return FALSE;
    }


    float t0_ = (-b - sqrtf(discriminant)) / (2.0f * a);
    float t1_ = (-b + sqrtf(discriminant)) / (2.0f * a);


    float s0 = ft_xyz_dot(&OC, &V) + t0_ * ft_xyz_dot(D, &V);
    float s1 = ft_xyz_dot(&OC, &V) + t1_ * ft_xyz_dot(D, &V);

    if (s0 < -h && s1 < -h) {

        return FALSE;
    }
    if (s0 > h && s1 > h) {

        return FALSE;
    }


    float t = (s0 > -h && s0 < h) ? t0_ : t1_;

    *t1 = t;
    return TRUE;
}

