/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   'structs.h'                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaron  <lbaron@student.42berlin.de>       :+:  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023-10-12 14:43:35 by lbaron            :+:    #+#             */
/*   Updated: 2023-10-12 14:43:35 by lbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "miniRT.h"

typedef struct s_matrix_3x3 {
	float	data[3][3];
}t_matrix_3x3;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}t_color;

typedef struct s_xyz
{
	float	x;
	float	y;
	float	z;
}t_xyz;

typedef struct s_xy
{
	float	x;
	float	y;
}t_xy;

typedef struct s_mat_utils
{
	t_xy			xy_ox;
	t_xy			xy_oy;
	t_xy			zx_v1;
	t_xyz			v1_1;
	t_xy			yz_v1_1;
	t_xy			zx_v2;
	t_xyz			v2_1;
	t_xy			yz_v2_1;

	t_matrix_3x3	rot_mat_1_oy;
	t_matrix_3x3	rot_mat_1_ox;
	t_matrix_3x3	rot_mat_2_oy_trnsp;
	t_matrix_3x3	rot_mat_2_ox_trnsp;
}t_mat_utils;

typedef struct s_all_m
{
	t_matrix_3x3	rot_mat_2_oy;
	t_matrix_3x3	rot_mat_2_ox;
	t_matrix_3x3	rot_mat_1;
	t_matrix_3x3	rot_mat_2;
}t_all_m;

typedef struct s_m_rows
{
	t_xyz	row1;
	t_xyz	row2;
	t_xyz	row3;
}t_m_rows;

//ambiant light
typedef struct s_ambient
{
	char	*id;
	float	ratio;
	t_color	color;
}t_ambient;

typedef struct s_cam
{
	char			*id;
	float			fov;
	t_xyz			coord;
	t_xyz			vector;
	t_matrix_3x3	rot;
}t_cam;

typedef struct s_light 
{
	char	*id;
	float	ratio;
	t_xyz	coord;
}t_light;

enum e_figure
{
	UNKNOWN,
	PLANE,
	SPHERE,
	CYLINDER
};

typedef struct s_sphere 
{
	char	*id;
	t_xyz	coord;
	float	r;
	t_color	color;
}t_sphere;

typedef struct s_plane
{
	char	*id;
	t_xyz	coord;
	t_xyz	vector;
	t_color	color;
}t_plane;

typedef struct s_cylinder 
{
	char	*id;
	t_xyz	coord;
	t_xyz	vector;
	float	diameter;
	float	height;
	t_color	color;
}t_cylinder;

union u_figures
{
	t_sphere	sp;
	t_plane		pl;
	t_cylinder	cy;
};

//linked list of all objects in the sc
typedef struct s_objects
{
	int					i;
	enum e_figure		type;
	union u_figures		fig;
	struct s_objects	*next;
}t_objects;

typedef struct s_canva
{
	int		x;
	int		y;
	int		scale;
	int		amb_intensity;
	float	depth_scale;
}t_canva;

typedef struct s_hitPoint
{
	float	h1;
	float	h2;
}t_hitPoint;

//struct for a sc (image that we render)
//it should have an ambient and normal light, 1 cam and some objects
typedef struct s_sc 
{
	t_ambient	ambient;
	t_cam		cam;
	t_light		light;
	t_objects	*objs;
	t_canva		canva;
}t_sc;

typedef struct s_window 
{
	mlx_t		*mlx;
	mlx_image_t	*img;
}t_window;

//our main struct
typedef struct s_rt 
{
	t_sc		*sc;
	t_window	*window;
}t_rt;

typedef struct s_int
{
	t_xyz		*o;
	t_xyz		*d;
	float		t_min;

}t_int;

typedef struct s_ks
{
	float	k1;
	float	k2;
	float	k3;
}t_ks;

typedef struct s_rays
{
	t_xyz	cb;
	t_xyz	v;
	t_xyz	oc;
	float	r;
	float	h;
	float	r_surrounding_sphere;
	float	a;
	float	b;
	float	c;
	float	discriminant;
	float	t0_;
	float	t1_;
	t_xyz	point;
	float	distance;
}t_rays;

typedef struct s_ray_caps
{
	t_plane	top;
	t_plane	bottom;
	float	half_h;
	t_xyz	norm;
	t_xyz	half_h_norm;
	float	t_top;
	float	t_bottom;
	int		top_intersected;
	int		bottom_intersected;
}t_ray_caps;

typedef struct s_cpt_light
{
	t_ambient	amb;
	t_light		light_point;
	float		i;
	float		s;
	t_xyz		l;
	t_objects	*shadow_object;
	t_int		param;
	float		n_dot_l;
	t_xyz		v_2n;
	float		dot_nl;
	t_xyz		a;
	t_xyz		r;
	float		r_dot_v;
	float		b;
}t_cpt_light;

typedef struct s_tra_ray
{
	t_int		param;
	float		closest_t;
	t_objects	*closest_object;
	t_xyz		p;
	t_xyz		n;
	t_color		color;
	t_xyz		min_d;
	float		i;
	t_color		fin_color;
	t_cylinder	*cylinder;
}t_tra_ray;

#endif