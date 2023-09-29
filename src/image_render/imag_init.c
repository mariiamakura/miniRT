/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imag_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:39:27 by mparasku          #+#    #+#             */
/*   Updated: 2023/09/29 14:44:19 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_xyz CanvasToViewport(int x, int y, int fov) {

    float d = Vw / (2 * tan((float) fov / 2 * M_PI / 180));
    return (t_xyz) {(float) x * Vw / Cw, (float) y * Vh / Ch, d};
}

t_xyz ft_get_intersec(t_xyz *O, float closest_t, t_xyz *D) {
    t_xyz P;

    // Compute intersection
    P.x = O->x + closest_t * D->x;
    P.y = O->y + closest_t * D->y;
    P.z = O->z + closest_t * D->z;

    return (P);
}

float ComputeLighting(t_xyz *P, t_xyz *N, t_rt **rt, t_xyz *V) {
    t_ambient amb = (*rt)->scene->ambient;
    t_light light_point = (*rt)->scene->light;
    float i = 0.0;
    float s = 150; //spectacular light

    if (amb.ratio == 0.0)
        i = 0.1;
    else if (amb.ratio == 1.0)
        i = 0.9;
    else {
        i += amb.ratio; //ambient included to the color intencity
    }

    t_xyz L = ft_minus(&light_point.coord, P);

    t_sphere *shadow_sphere = NULL;
    ClosestIntersection(rt, P, &L, &shadow_sphere, 0.001);
    if (shadow_sphere != NULL)
        return (i);

    float n_dot_l = ft_dot(N, &L);
    if (n_dot_l > 0) {
        i += light_point.ratio * n_dot_l / (ft_vec_lenght(N) * ft_vec_lenght(&L));

    }

    //spectacular light
    t_xyz v_2N = ft_vec_mult_float(N, 2.0);
    float dot_NL = ft_dot(N, &L);
    t_xyz a = ft_vec_mult_float(&v_2N, dot_NL);
    t_xyz R = ft_minus(&a, &L);
    float r_dot_v = ft_dot(&R, V);

    if (r_dot_v > 0) {
        float b = r_dot_v / (ft_vec_lenght(&R) * ft_vec_lenght(V));
        i += light_point.ratio * powf(b, s);
    }
    return (i);
}


int IntersectRaySphere(t_xyz *O, t_xyz *D, t_sphere *sphere, float *t1, float *t2) {
    t_xyz * C = &sphere->coord;
    float r = sphere->r;
    t_xyz OC = ft_minus(O, C);

    float k1 = ft_dot(D, D);
    float k2 = 2 * ft_dot(&OC, D);
    float k3 = ft_dot(&OC, &OC) - r * r;

    float discriminant = k2 * k2 - 4 * k1 * k3;
    if (discriminant < 0) {
        return FALSE;
    }

    *t1 = (-k2 + sqrt(discriminant)) / (2 * k1);
    *t2 = (-k2 - sqrt(discriminant)) / (2 * k1);
    return TRUE;
}


float ClosestIntersection(t_rt **rt, t_xyz *O, t_xyz *D, t_sphere **closest_sphere, float t_min) {
    float closest_t = FLT_MAX;
    float t1, t2;
    t_objects *object = (*rt)->scene->objs;
    while (object != NULL) {
        if (object->type == SPHERE) {
            t_sphere *sphere = &(object->fig.sp);
            if (IntersectRaySphere(O, D, sphere, &t1, &t2)) {
                if (t1 > t_min && t1 < closest_t) { //if t > d I found with fov
                    closest_t = t1;
                    *closest_sphere = sphere;
                }
                if (t1 > t_min && t2 < closest_t) {
                    closest_t = t2;
                    *closest_sphere = sphere;
                }
            }
        }
        object = object->next;
    }
    return (closest_t);
}

t_color TraceRay(t_rt **rt, t_xyz *O, t_xyz *D) {
    float closest_t = FLT_MAX;
    t_sphere *closest_sphere = NULL;
    t_color fin_color;

    closest_t = ClosestIntersection(rt, O, D, &closest_sphere, 1);

    if (closest_sphere == NULL) {
        return (t_color) {0, 0, 0};
    } else {
        //printf("closest sphere %i %i\n", closest_sphere->color.r, closest_sphere->color.g);
        t_xyz P = ft_get_intersec(O, closest_t, D);   //intersec point of sphere
        t_xyz N = ft_minus(&P, &closest_sphere->coord);// Compute sphere normal at intersection
        N = ft_normalize(&N);

        //printf("%f %f %f\n", N.x, N.y, N.z);
        t_xyz min_D = ft_unary_minus(D);
        float i = ComputeLighting(&P, &N, rt, &min_D);
        fin_color = ft_set_fin_color(&closest_sphere->color, i);
        return fin_color;
    }
}

void draw_ball(t_rt **rt) {
    t_xyz O = (*rt)->scene->camera.coord;
    t_xyz V = {0, 0, 1};
    t_xyz camV = (*rt)->scene->camera.vector;
    float[3][3] rotate = ft_rotate(V, camV);
    int fov = (*rt)->scene->camera.fov;
    for (int Sx = 0; Sx < Cw; Sx++) {
        for (int Sy = 0; Sy < Ch; Sy++) {
            int Cx = Sx - Cw / 2;
            int Cy = Ch / 2 - Sy;
            t_xyz D = rotate * CanvasToViewport(Cx, Cy, fov); //rotate to be implemented
            t_color color = TraceRay(rt, &O, &D);
            uint32_t fin_color = ft_pixel(color.r, color.g, color.b, 255);
            mlx_put_pixel((*rt)->window->img, Sx, Sy, fin_color);
        }
    }
}

void ft_hook(void *param) {
    t_rt *rt;

    rt = (t_rt *) param;
    if (mlx_is_key_down(rt->window->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(rt->window->mlx);
    if (mlx_is_key_down(rt->window->mlx, MLX_KEY_UP))
        rt->window->img->instances[0].y -= 5;
    if (mlx_is_key_down(rt->window->mlx, MLX_KEY_DOWN))
        rt->window->img->instances[0].y += 5;
    if (mlx_is_key_down(rt->window->mlx, MLX_KEY_LEFT))
        rt->window->img->instances[0].x -= 5;
    if (mlx_is_key_down(rt->window->mlx, MLX_KEY_RIGHT))
        rt->window->img->instances[0].x += 5;
}

int ft_imag_init(t_rt **rt) {
    (*rt)->window = malloc(sizeof(t_window));
    if (!(*rt)->window)
        return (ft_error("mlx error"));
    (*rt)->window->mlx = mlx_init(Cw, Ch, "miniRT", true);
    if (!(*rt)->window->mlx)
        return (ft_error("mlx error"));
    (*rt)->window->img = mlx_new_image((*rt)->window->mlx, Cw, Ch);
    if (!(*rt)->window->img) {
        mlx_close_window((*rt)->window->mlx);
        return (ft_error("img error"));
    }
    if (mlx_image_to_window((*rt)->window->mlx, (*rt)->window->img, 0, 0) == -1) {
        mlx_close_window((*rt)->window->mlx);
        return (ft_error("img error"));
    }
    mlx_loop_hook((*rt)->window->mlx, ft_hook, (*rt));
    //ft_camera_orient(rt);
    draw_ball(rt);
    //mlx_key_hook((*rt)->window->mlx, ft_key_callback, (*rt));
    mlx_loop((*rt)->window->mlx);
    return (TRUE);
}
