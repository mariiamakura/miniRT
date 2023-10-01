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
	float d = (float)fov / 60;
    return (t_xyz) {(float) x * Vw / Cw, (float) y * Vh / Ch, d};
}

int IntersectRaySphere(t_xyz *O, t_xyz *D, t_sphere *sphere, float *t1, float *t2) {
    t_xyz *C = &sphere->coord;
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

int IntersectRayPlane(t_xyz *O, t_xyz *D, t_plane *plane, float *t) {
	t_xyz normal = plane->vector; // Assuming plane->vector is already normalized
	t_xyz diff = ft_minus(&plane->coord, O);
	float denom = ft_dot(&normal, D);

	if (fabs(denom) > 1e-6) { // Avoid division by zero and handle parallel case
		*t = ft_dot(&diff, &normal) / denom;
		if (*t >= 0) return TRUE; // Change this condition based on your coordinate system and direction
	}
	return FALSE;
}

t_xyz ft_get_intersec(t_xyz *O, float closest_t, t_xyz *D)
{
	t_xyz P;

	// Compute intersection
	P.x = O->x + closest_t * D->x;
	P.y = O->y + closest_t * D->y;
	P.z = O->z + closest_t * D->z;

	return (P);
}

float ComputeLighting(t_xyz *P, t_xyz *N, t_rt **rt) {
	t_ambient amb = (*rt)->scene->ambient;
	t_light light_point = (*rt)->scene->light;
	float i = amb.ratio;

	t_xyz L = ft_minus(&light_point.coord, P);
	float n_dot_l = ft_dot(N, &L);
	if (n_dot_l > 0) {
		i += light_point.ratio * n_dot_l / (ft_vec_lenght(N) * ft_vec_lenght(&L));
	}

	return i;
}

t_color TraceRay(t_rt **rt, t_xyz *O, t_xyz *D) {
	float t;
	float t1, t2;
	float closest_t = FLT_MAX;
	enum e_figure closest_figure = UNKNOWN;
	t_color closest_color;
	t_sphere *closest_sphere = NULL;
	t_plane *closest_plane = NULL;

	t_objects *object = (*rt)->scene->objs;
	while (object != NULL) {
		if (object->type == SPHERE) {
			t_sphere *sphere = &(object->fig.sp);
			if (IntersectRaySphere(O, D, sphere, &t1, &t2)) {
				if (t1 < closest_t && t1 >= 0) {
					closest_t = t1;
					closest_figure = SPHERE;
					closest_color = sphere->color;
					closest_sphere = sphere;
				}
			}
		}
		else if (object->type == PLANE) {
			t_plane *plane = &(object->fig.pl);
			if (IntersectRayPlane(O, D, plane, &t)) {
				if (t < closest_t && t >= 0) {
					closest_t = t;
					closest_figure = PLANE;
					closest_color = plane->color;
					closest_plane = plane;
				}
			}
		}
		object = object->next;
	}

	if (closest_figure == UNKNOWN) {
		return (t_color){0, 0, 0};
	}
	else {
		t_xyz P = ft_get_intersec(O, closest_t, D);
		t_xyz N;
		if (closest_figure == SPHERE && closest_sphere != NULL) {
			N = ft_minus(&P, &closest_sphere->coord);  // Use the closest sphere here
		} else if (closest_figure == PLANE && closest_plane != NULL) {
			N = closest_plane->vector;  // Use the closest plane here
		}
		N = ft_normalize(&N);

		float i = ComputeLighting(&P, &N, rt);
		closest_color.r *= i;
		closest_color.g *= i;
		closest_color.b *= i;

		// Clip the colors to the range [0, 255]
		closest_color.r = fminf(fmaxf(closest_color.r, 0), 255);
		closest_color.g = fminf(fmaxf(closest_color.g, 0), 255);
		closest_color.b = fminf(fmaxf(closest_color.b, 0), 255);
		return closest_color;
	}
}

void draw_ball(t_rt **rt) {
    t_xyz O = (*rt)->scene->camera.coord;
	int fov = (*rt)->scene->camera.fov;
    for (int Sx = 0; Sx < Cw; Sx++) {
        for (int Sy = 0; Sy < Ch; Sy++) {
            int Cx = Sx - Cw / 2;
            int Cy = Ch / 2 - Sy;
            t_xyz D = CanvasToViewport(Cx, Cy, fov);
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
