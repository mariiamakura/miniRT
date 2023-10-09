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

int PointInsideCap(t_xyz *P, t_cylinder *cylinder) {
	t_xyz v = ft_xyz_minus(P, &cylinder->coord);
	return ft_xyz_dot(&v, &v) <= (cylinder->diameter / 2) * (cylinder->diameter / 2);
}

int IntersectRayCap(t_xyz *O, t_xyz *D, t_cylinder *cylinder, float *t, int isTopCap) {
	t_xyz temp = ft_xyz_mul_num(&cylinder->vector, cylinder->height);
	t_xyz capCenter;
	t_xyz normal;

	if (isTopCap)
	{
		capCenter = ft_xyz_plus(&cylinder->coord, &temp);
		normal = cylinder->vector;
	}
	else
	{
		capCenter = cylinder->coord;
		normal = ft_xyz_unary_minus(&cylinder->vector);
	}

	float denominator = ft_xyz_dot(D, &normal);
	if (fabs(denominator) < 0.0001f) {
		return FALSE;
	}

	t_xyz OC = ft_xyz_minus(O, &capCenter);
	*t = -ft_xyz_dot(&OC, &normal) / denominator;

	if (*t < 0.0f) {
		return FALSE;
	}

	t_xyz P = ft_get_intersec(O, *t, D);
	return PointInsideCap(&P, cylinder);
}

int IntersectRayCylinder(t_xyz *O, t_xyz *D, t_cylinder *cylinder, float *t1, float *t2) {
    t_xyz C = cylinder->coord;
    float r = cylinder->diameter / 2.0;
    float h = cylinder->height;

    t_xyz OC = ft_xyz_minus(O, &C);
    t_xyz OD = *D;

    float a = OD.x * OD.x + OD.z * OD.z;
    float b = 2 * (OC.x * OD.x + OC.z * OD.z);
    float c = OC.x * OC.x + OC.z * OC.z - r * r;

    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return FALSE; // No intersection
    }

    // Compute the two solutions for t
    float t1_ = (-b + sqrt(discriminant)) / (2 * a);
    float t2_ = (-b - sqrt(discriminant)) / (2 * a);

    // Check if the intersection points are within the height of the cylinder
    float y1 = O->y + t1_ * OD.y;
    float y2 = O->y + t2_ * OD.y;

    if ((y1 >= -h && y1 <= h) || (y2 >= -h && y2 <= h)) {
        // At least one intersection point is within the cylinder height
        *t1 = t1_;
        *t2 = t2_;
        return TRUE;
    } else {
        return FALSE; // Both intersection points are outside the cylinder height
    }
}
