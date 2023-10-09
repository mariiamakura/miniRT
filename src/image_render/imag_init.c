/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imag_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:39:27 by mparasku          #+#    #+#             */
/*   Updated: 2023/10/06 18:00:55 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_xyz	ft_can_to_vport(int x, int y, int fov)
{
	float	distance;
	t_xyz	res;

	distance = Vw / (2 * tan((float) fov / 2 * M_PI / 180));
	res.x = (float) x * Vw / Cw;
	res.y = (float) y * Vh / Ch;
	res.z = distance;
	return (res);
}

t_xyz ft_get_intersec(t_xyz *O, float closest_t, t_xyz *D) {
    t_xyz P;

    // Compute intersection
    P.x = O->x + closest_t * D->x;
    P.y = O->y + closest_t * D->y;
    P.z = O->z + closest_t * D->z;

    return (P);
}

float ComputeLighting(t_xyz *P, t_xyz *N, t_rt **rt, t_xyz *V)
{
	t_ambient amb = (*rt)->sc->ambient;
	t_light light_point = (*rt)->sc->light;
	float i = 0.0;
	float s = 150;

	if (amb.ratio == 0.0)
		i = 0.1;
	else if (amb.ratio == 1.0)
		i = 0.9;
	else {
		i += amb.ratio;
	}

	t_xyz L = ft_xyz_minus(&light_point.coord, P);

	t_objects *shadow_object = NULL;
	ClosestIntersection(rt, P, &L, &shadow_object, 0.001);
	if (shadow_object != NULL)
		return (i);
	float n_dot_l = ft_xyz_dot(N, &L);
	if (n_dot_l > 0)
	{
		i += light_point.ratio * n_dot_l / (ft_xyz_length(N) * ft_xyz_length(&L));
	}

	t_xyz v_2N = ft_xyz_mul_num(N, 2.0);
	float dot_NL  = ft_xyz_dot(N, &L);
	t_xyz a = ft_xyz_mul_num(&v_2N, dot_NL);
	t_xyz R = ft_xyz_minus(&a, &L);
	float r_dot_v = ft_xyz_dot(&R, V);

	if (r_dot_v > 0) {
		float b = r_dot_v / (ft_xyz_length(&R) * ft_xyz_length(V));
		i += light_point.ratio * powf(b, s);
	}
	return (i);
}

//float ComputeLighting(t_xyz *P, t_xyz *N, t_rt **rt, t_xyz *V) {
//    t_ambient amb = (*rt)->sc->ambient;
//    t_light light_point = (*rt)->sc->light;
//    float i = 0.0;
//    float s = 150; //spectacular light
//
//    if (amb.ratio == 0.0)
//        i = 0.1;
//    else if (amb.ratio == 1.0)
//        i = 0.9;
//    else {
//        i += amb.ratio; //ambient included to the color intencity
//    }
//
//    t_xyz L = ft_xyz_minus(&light_point.coord, P);
//
//    t_sphere *shadow_sphere = NULL;
//    ClosestIntersection(rt, P, &L, &shadow_sphere, 0.001);
//    if (shadow_sphere != NULL)
//        return (i);
//
//    float n_dot_l = ft_xyz_dot(N, &L);
//    if (n_dot_l > 0) {
//        i += light_point.ratio * n_dot_l / (ft_xyz_length(N) * ft_xyz_length(&L));
//
//    }
//
//    //spectacular light
//    t_xyz v_2N = ft_xyz_mul_num(N, 2.0);
//    float dot_NL = ft_xyz_dot(N, &L);
//    t_xyz a = ft_xyz_mul_num(&v_2N, dot_NL);
//    t_xyz R = ft_xyz_minus(&a, &L);
//    float r_dot_v = ft_xyz_dot(&R, V);
//
//    if (r_dot_v > 0) {
//        float b = r_dot_v / (ft_xyz_length(&R) * ft_xyz_length(V));
//        i += light_point.ratio * powf(b, s);
//    }
//    return (i);
//}
//
//
//int IntersectRaySphere(t_xyz *O, t_xyz *D, t_sphere *sphere, float *t1, float *t2) {
//    t_xyz * C = &sphere->coord;
//    float r = sphere->r;
//    t_xyz OC = ft_xyz_minus(O, C);
//
//    float k1 = ft_xyz_dot(D, D);
//    float k2 = 2 * ft_xyz_dot(&OC, D);
//    float k3 = ft_xyz_dot(&OC, &OC) - r * r;
//
//    float discriminant = k2 * k2 - 4 * k1 * k3;
//    if (discriminant < 0) {
//        return FALSE;
//    }
//
//    *t1 = (-k2 + sqrt(discriminant)) / (2 * k1);
//    *t2 = (-k2 - sqrt(discriminant)) / (2 * k1);
//    return TRUE;
//}
//
//
//float ClosestIntersection(t_rt **rt, t_xyz *O, t_xyz *D, t_sphere **closest_sphere, float t_min) {
//    float closest_t = FLT_MAX;
//    float t1, t2;
//    t_objects *object = (*rt)->sc->objs;
//    while (object != NULL) {
//        if (object->type == SPHERE) {
//            t_sphere *sphere = &(object->fig.sp);
//            if (IntersectRaySphere(O, D, sphere, &t1, &t2)) {
//                if (t1 > t_min && t1 < closest_t) { //if t > d I found with fov
//                    closest_t = t1;
//                    *closest_sphere = sphere;
//                }
//                if (t1 > t_min && t2 < closest_t) {
//                    closest_t = t2;
//                    *closest_sphere = sphere;
//                }
//            }
//        }
//        object = object->next;
//    }
//    return (closest_t);
//}
//
//t_color TraceRay(t_rt **rt, t_xyz *O, t_xyz *D) {
//    float closest_t = FLT_MAX;
//    t_sphere *closest_sphere = NULL;
//    t_color fin_color;
//
//    closest_t = ClosestIntersection(rt, O, D, &closest_sphere, 1);
//
//    if (closest_sphere == NULL) {
//        return (t_color) {0, 0, 0};
//    } else {
//        //printf("closest sphere %i %i\n", closest_sphere->color.r, closest_sphere->color.g);
//        t_xyz P = ft_get_intersec(O, closest_t, D);   //intersec point of sphere
//        t_xyz N = ft_xyz_minus(&P, &closest_sphere->coord);// Compute sphere normal at intersection
//        N = ft_xyz_normalize(&N);
//
//        //printf("%f %f %f\n", N.x, N.y, N.z);
//        t_xyz min_D = ft_xyz_unary_minus(D);
//        float i = ComputeLighting(&P, &N, rt, &min_D);
//        fin_color = ft_set_fin_color(&closest_sphere->color, i);
//        return fin_color;
//    }
//}

int	ft_render_fun(t_rt **rt, int Cx, int Cy)
{
	t_xyz			o;
	t_matrix_3x3	rot;
	t_xyz			can_to_v;
	t_xyz			d;
	t_color			color;
	
	o = (*rt)->sc->cam.coord;
	rot = (*rt)->sc->cam.rot;
	can_to_v = ft_can_to_vport(Cx, Cy, (*rt)->sc->cam.fov);
	d = ft_mat_mul_xyz(&rot, &can_to_v);
	color = TraceRay(rt, &o, &d);
	return(ft_pixel(color.r, color.g, color.b, 255));
}

void render_sc(t_rt **rt)
{
	int Sx;
	int Sy;
	int Cx;
	int Cy;
	int fin_color;

	Sx = 0;
	while (Sx < Cw)
	{
		Sy = 0;
		while (Sy < Ch)
		{
			Cx = Sx - Cw / 2;
			Cy = Ch / 2 - Sy;
			fin_color= ft_render_fun(rt, Cx, Cy);
			mlx_put_pixel((*rt)->window->img, Sx, Sy, fin_color);
			Sy++;
		}
		Sx++;
	}
}

void	ft_hook(void *param)
{
	t_rt **rt;

	rt = (t_rt **) param;
	
	ft_process_cam_movement(rt);
	ft_process_cam_rotation(rt);
	render_sc(rt);
}

int	ft_imag_init(t_rt **rt)
{
	(*rt)->window = malloc(sizeof(t_window));
	if (!(*rt)->window)
		return (ft_error("mlx error"));
	(*rt)->window->mlx = mlx_init(Cw, Ch, "miniRT", true);
	if (!(*rt)->window->mlx)
		return (ft_error("mlx error"));
	(*rt)->window->img = mlx_new_image((*rt)->window->mlx, Cw, Ch);
	if (!(*rt)->window->img)
	{
		mlx_close_window((*rt)->window->mlx);
		return (ft_error("img error"));
	}
	if (mlx_image_to_window((*rt)->window->mlx, (*rt)->window->img, 0, 0) == -1)
	{
		mlx_close_window((*rt)->window->mlx);
		return (ft_error("img error"));
	}
	mlx_loop_hook((*rt)->window->mlx, ft_hook, rt);
	mlx_loop((*rt)->window->mlx);
	return (TRUE);
}