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
    t_xyz p = *O; //ray origin
    t_xyz pa = cylinder->coord; //cylinder axis point (center line) {0,0,0}
    t_xyz v = *D; //ray direction
    t_xyz va = cylinder->vector; //cylinder direction {0,1,0}
    float r = cylinder->diameter / 2.0; //{0.5}
    float h = cylinder->height;

    t_xyz delta_p = ft_xyz_minus(&p, &pa); //p - pa

    float dot_product = ft_xyz_dot(&v, &va);

    t_xyz A;
    A.x = v.x - dot_product * va.x;
    A.y = v.y - dot_product * va.y;
    A.z = v.z - dot_product * va.z;

    float dot_product2 = ft_xyz_dot(&delta_p, &va);
    t_xyz B;

    B.x = 2.0 * (A.x * delta_p.x - dot_product2 * A.x * va.x);
    B.y = 2.0 * (A.y * delta_p.y - dot_product2 * A.y * va.y);
    B.z = 2.0 * (A.z * delta_p.z - dot_product2 * A.z * va.z);

    float dot_product3 = ft_xyz_dot(&delta_p, &v);
    float C = dot_product3 * dot_product3 - r * r;

    double discriminant = B.x * B.x + B.y * B.y + B.z * B.z - 4.0 * A.x * C;

    if (discriminant < 0) {
        //printf("no solutions");
        return FALSE; // No real solutions, no intersection
    }
        // Calculate the two possible values of t
    float t1_ = (-B.x + sqrt(discriminant)) / (2.0 * A.x);
    float t2_ = (-B.x - sqrt(discriminant)) / (2.0 * A.x);
    *t1 = t1_;
    *t2 = t2_;

    if (t1_ <= h && t1_ >= 0) {
        printf("t1 %f\n", t1_);
        *t1 = t1_;
    }
    else {
        printf("t1 does not satisfy conditions: t1_ = %f\n", t1_);
    }
    if (t2_ <= h && t2_ >= 0){
        printf("t2 %f\n", t2_);
        *t2 = t2_;
    }
    return TRUE;
}