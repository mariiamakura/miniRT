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
    //float h = cylinder->height;

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

    return TRUE;
}

int IntersectRayCylinderCaps(t_xyz *O, t_xyz *D, t_cylinder *cylinder, float *tCap1, float *tCap2, float t_min, float closest_t) {
    // Calculate the parameters for the planes of the cylinder caps
    t_xyz p1 = cylinder->coord; // Center of the bottom cap
    t_xyz p2; // Center of the top cap
    p2.x = p1.x + cylinder->vector.x * cylinder->height;
    p2.y = p1.y + cylinder->vector.y * cylinder->height;
    p2.z = p1.z + cylinder->vector.z * cylinder->height;

    // Calculate the normal vectors of the caps
    t_xyz normal1 = cylinder->vector; // Normal of the bottom cap
    t_xyz normal2; // Normal of the top cap
    normal2.x = -cylinder->vector.x;
    normal2.y = -cylinder->vector.y;
    normal2.z = -cylinder->vector.z;

    // Calculate t values for the intersections with the caps
    t_xyz a1 = ft_xyz_minus(&p1, O);
    float tCap1_ = ft_xyz_dot(&a1, &normal1) / ft_xyz_dot(D, &normal1);
    t_xyz a2 = ft_xyz_minus(&p2, O);
    float tCap2_ = ft_xyz_dot(&a2, &normal2) / ft_xyz_dot(D, &normal2);

    // Check if the intersections are valid and within the caps' bounds
    if (tCap1_ > t_min && tCap1_ < closest_t) {
        t_xyz q1;
        q1.x = O->x + tCap1_ * D->x;
        q1.y = O->y + tCap1_ * D->y;
        q1.z = O->z + tCap1_ * D->z;

        float distance1 = (q1.x - p1.x) * (q1.x - p1.x) + (q1.z - p1.z) * (q1.z - p1.z);

        if (distance1 <= (cylinder->diameter / 2.0) * (cylinder->diameter / 2.0)) {
            *tCap1 = tCap1_;
            return TRUE;
        }
    }

    if (tCap2_ > t_min && tCap2_ < closest_t) {
        t_xyz q2;
        q2.x = O->x + tCap2_ * D->x;
        q2.y = O->y + tCap2_ * D->y;
        q2.z = O->z + tCap2_ * D->z;

        float distance2 = (q2.x - p2.x) * (q2.x - p2.x) + (q2.z - p2.z) * (q2.z - p2.z);

        if (distance2 <= (cylinder->diameter / 2.0) * (cylinder->diameter / 2.0)) {
            *tCap2 = tCap2_;
            return TRUE;
        }
    }

    return FALSE;
}
