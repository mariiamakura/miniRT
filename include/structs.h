#ifndef STRUCTS_H
#define STRUCTS_H

#include "miniRT.h"


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

//struct for a scene (image that we render)
//it should have an ambient and normal light, 1 camera and some objects
typedef struct s_scene 
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_objects	*objs;
} t_scene;


//our main struct
typedef struct s_rt 
{
	t_scene *scene;
} t_rt;

#endif