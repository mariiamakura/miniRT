#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "miniRT.h"

//parse.c
int ft_file_validation(char *file);
int ft_parse(char *file, t_rt **rt);
int	ft_fill_structs(int fd, t_rt **rt, int index);

//parse_utils.c
int ft_error(char *err_msg);
int ft_count_arr_elements(char **tab);
void ft_free_2d_arr(char **tab);

//check_file_content.c
int ft_check_extention(char *file);
char *ft_file_to_str(char *file);
int ft_elements_num(char *file_str);

//init_parse_struct.c
int ft_init_parse_rt(t_rt **rt);

//light_camera_parse.c
int	ft_ambient_light_parse(char *line, t_rt **rt);
int ft_camera_parse(char *line, t_rt **rt);
int ft_light_parse(char *line, t_rt **rt);

//parse_ratio_color.c
int ft_parse_ratio(char *str, float *ratio);
int ft_is_float(char *str);
float ft_str_to_float(char *str);
int ft_parse_color(char *str, t_color *colors);
int is_color(char *str);

//parse_coord_vec.c
int ft_parse_coord(char *line, t_xyz *coord);
int ft_parse_vectors(char *line, t_xyz *vectors);
int ft_is_range(float num);
int ft_parse_fov(char *line, float *fov);
int ft_parse_num_var(char *line, float *num);

//ft_manage_list.c
t_objects *last_obj(t_objects *objs);
void ft_add_obj(t_objects **objs, t_objects *new);

//parse_objects.c
int	ft_parse_objects(char *line, t_rt **rt, int index);
int ft_sphere_parse(char *line, t_sphere *sp);
int ft_parse_cylinder(char *line, t_cylinder *cy);
int ft_plane_parse(char *line, t_plane *pl);

//ft_free.c
void ft_free_rt(t_rt *rt);
void ft_print_all(t_rt *rt);
//static void ft_free_objects(t_objects *objs);

//image_render
//imag_init.c
int ft_imag_init(t_rt **rt);
void ft_key_callback(mlx_key_data_t key_data, void *rt);
void draw_ball(t_rt **rt);;
void ft_get_viewpoint(int x, int y, t_xyz *viewPoint/*, t_rt **rt*/);
float ClosestIntersection(t_rt **rt, t_xyz *O, t_xyz *D, t_objects **closest_object, float t_min);

//camera.c
void	ft_camera_orient(t_rt **rt);

//colors.c
void ft_gradient(t_color *color, t_rt **rt);
void ft_put_pixel(int x, int y, int color, t_rt **rt);
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
t_color ft_set_fin_color(t_color *origin, float i);

//math.c
float ft_dot(t_xyz *vec1, t_xyz *vec2);
t_xyz ft_unary_minus(t_xyz *vec);
t_xyz ft_plus(t_xyz *vec1, t_xyz *vec2);
t_xyz ft_minus(t_xyz *vec1, t_xyz *vec2);
t_xyz ft_normalize(t_xyz *vec);
float ft_vec_lenght(t_xyz *vec);
t_xyz ft_vec_mult_float(t_xyz *vec, float i);
t_xyz ft_vec_multi(t_xyz *vec1, t_xyz *vec2);

#endif