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
	t_xyz OC = ft_xyz_minus(O, &cylinder->coord); //OC is calculated as the vector from the ray origin O to the cylinder's center.
	t_xyz V = cylinder->vector;

	t_xyz temp = ft_xyz_mul_num(&V, ft_xyz_dot(D, &V));
	t_xyz DP;
	DP.x = D->x - temp.x;
	DP.y = D->y - temp.y;
	DP.z = D->z - temp.z;

	temp = ft_xyz_mul_num(&V, ft_xyz_dot(&OC, &V));
	t_xyz OCp;
	OCp.x = OC.x - temp.x;
	OCp.y = OC.y - temp.y;
	OCp.z = OC.z - temp.z;

	float A = ft_xyz_dot(&DP, &DP);
	float B = 2 * ft_xyz_dot(&OCp, &DP);
	float C = ft_xyz_dot(&OCp, &OCp) - (cylinder->diameter / 2) * (cylinder->diameter / 2);

	float discriminant = B * B - 4 * A * C;
	if (discriminant < 0) {
		return FALSE;
	}

	float tempT1 = (-B + sqrt(discriminant)) / (2 * A);
	float tempT2 = (-B - sqrt(discriminant)) / (2 * A);

	t_xyz tempP1 = ft_xyz_mul_num(D, tempT1);
	t_xyz P1 = ft_xyz_plus(O, &tempP1);
	t_xyz tempP2 = ft_xyz_mul_num(D, tempT2);
	t_xyz P2 = ft_xyz_plus(O, &tempP2);

	t_xyz tempH1 = ft_xyz_minus(&P1, &cylinder->coord);
	float height1 = ft_xyz_dot(&V, &tempH1);
	t_xyz tempH2 = ft_xyz_minus(&P2, &cylinder->coord);
	float height2 = ft_xyz_dot(&V, &tempH2);

	if (height1 >= 0 && height1 <= cylinder->height) {
		*t1 = tempT1;
	} else {
		*t1 = FLT_MAX;
	}

	if (height2 >= 0 && height2 <= cylinder->height) {
		*t2 = tempT2;
	} else {
		*t2 = FLT_MAX;
	}

	if (*t1 == FLT_MAX && *t2 == FLT_MAX) {
		return FALSE;
	}

	return TRUE;
}