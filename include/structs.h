#ifndef STRUCTS_H
#define STRUCTS_H

#include "miniRT.h"


typedef struct s_matrix_3x3 {
    float data[3][3];
} t_matrix_3x3;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
} t_color;

typedef struct s_xyz
{
	float x;
	float y;
	float z;
} t_xyz;

typedef struct s_xy
{
    float x;
    float y;
} t_xy;


typedef struct s_mat_utils
{
	t_xy	xy_ox;
	t_xy	xy_oy;
	t_xy	zx_v1;
	t_xyz	v1_1;
	t_xy	yz_v1_1;
	t_xy	zx_v2;
	t_xyz	v2_1;
	t_xy	yz_v2_1;

	t_matrix_3x3 rot_mat_1_oy;
	t_matrix_3x3 rot_mat_1_ox;
	t_matrix_3x3 rot_mat_2_oy_trnsp;
	t_matrix_3x3 rot_mat_2_ox_trnsp;
} t_mat_utils;

typedef struct s_all_m
{
	t_matrix_3x3 rot_mat_2_oy;
	t_matrix_3x3 rot_mat_2_ox;
	t_matrix_3x3 rot_mat_1;
	t_matrix_3x3 rot_mat_2;
} t_all_m;


typedef struct s_m_rows
{
	 t_xyz row1;
	 t_xyz row2;
	 t_xyz row3;
} t_m_rows;

//ambiant light
typedef struct	s_ambient
{
	char	*id;
	float	ratio;
	t_color	color;
} t_ambient;


typedef struct	s_camera
{
    char	*id;
    float	fov;
    //t_color	color;
    t_xyz	coord;
    t_xyz	vector; //vector
} t_camera;

typedef struct s_light 
{
	char	*id;
	float ratio; //brightness
	t_xyz coord;
} t_light;

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
	t_xyz coord;
	float r; //radius
	t_color color;
} t_sphere;

typedef struct s_plane
{
	char	*id;
	t_xyz coord;
	t_xyz vector; //vector
	t_color color;
} t_plane;

typedef struct s_cylinder 
{
	char	*id;
	t_xyz coord;
	t_xyz vector;
	float diameter;
	float height;
	t_color color;
} t_cylinder;

union u_figures
{
	t_sphere	sp;
	t_plane		pl;
	t_cylinder	cy;
};

//linked list of all objects in the scene
typedef struct s_objects
{
	int	i;
	enum e_figure	type;
	union u_figures	fig;
	struct s_objects *next;
} t_objects;


typedef struct s_canva
{
	int x;
	int y;
	int scale;
	int amb_intensity;
	float depth_scale;
} t_canva;

typedef struct s_hitPoint
{
    float h1;
    float h2;
} t_hitPoint;

//struct for a scene (image that we render)
//it should have an ambient and normal light, 1 camera and some objects
typedef struct s_scene 
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_objects	*objs;
	t_canva		canva;
} t_scene;

typedef struct s_window 
{
	mlx_t *mlx;
	mlx_image_t *img;
} t_window;

//our main struct
typedef struct s_rt 
{
	t_scene *scene;
	t_window *window; //not initialized after parsing
} t_rt;

#endif