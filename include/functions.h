#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "miniRT.h"

//parse.c
int ft_file_validation(char *file);
int ft_parse(char *file, t_rt **rt);
int	ft_fill_structs(int fd, t_rt **rt, int index);
/* static int	ft_process_line(char *line, t_rt **rt, int *index); */

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
int ft_is_float(char *str);
float ft_str_to_float(char *str);
int ft_parse_color(char *str, t_color *colors);
int is_color(char *str);

//parse_coord_vec.c
int ft_parse_coord(char *line, t_xyz *coord);
int ft_parse_vectors(char *line, t_xyz *vectors);
int ft_parse_fov(char *line, float *fov);
int ft_parse_num_var(char *line, float *num);
/* static int	ft_vec_element(char *elm, t_xyz *vecs, int i); */

//ft_manage_list.c
t_objects *last_obj(t_objects *objs);
void ft_add_obj(t_objects **objs, t_objects *new);
int ft_is_range(float num);
int ft_parse_ratio(char *str, float *ratio);

//parse_objects.c
int ft_sphere_parse(char *line, t_sphere *sp);
int ft_parse_cylinder(char *line, t_cylinder *cy);
int ft_plane_parse(char *line, t_plane *pl);

//parse_objects_2.c
int	ft_parse_objects(char *line, t_rt **rt, int index);
int	parse_object_parameters(char *line, t_objects *new_obj);
t_objects	*create_object(int type);

//ft_free.c
void ft_free_rt(t_rt *rt);
void ft_print_all(t_rt *rt);
//static void ft_free_objects(t_objects *objs);

//image_render
//imag_init.c
int ft_imag_init(t_rt **rt);
float ClosestIntersection(t_rt **rt, t_xyz *O, t_xyz *D,t_sphere **closest_sphere, float t_min);

//camera.c
void	ft_camera_orient(t_rt **rt);

//colors.c
void ft_gradient(t_color *color, t_rt **rt);
void ft_put_pixel(int x, int y, int color, t_rt **rt);
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
t_color ft_set_fin_color(t_color *origin, float i);

//xy_math.c
void ft_xy_print(t_xy *vec);
float ft_xy_dot(t_xy *vec1, t_xy *vec2);
t_xyz ft_xy_mul(t_xy *vec1, t_xy *vec2);
float ft_xy_sin(t_xy *vec1, t_xy *vec2);
float ft_xy_cos(t_xy *vec1, t_xy *vec2);

//xyz_math.c
void ft_xyz_print(t_xyz *vec);
float ft_xyz_dot(t_xyz *vec1, t_xyz *vec2);
float ft_xyz_length(t_xyz *vec);
t_xyz ft_xyz_unary_minus(t_xyz *vec);
t_xyz ft_xyz_mul(t_xyz *vec1, t_xyz *vec2);
t_xyz ft_xyz_elm_mul(t_xyz *vec1, t_xyz *vec2);
t_xyz ft_xyz_mul_num(t_xyz *vec, float i);
t_xyz ft_xyz_plus(t_xyz *vec1, t_xyz *vec2);
t_xyz ft_xyz_minus(t_xyz *vec1, t_xyz *vec2);
t_xyz ft_xyz_normalize(t_xyz *vec);

//mat_math.c
void ft_mat_print(t_matrix_3x3 *mat);
t_xyz ft_mat_mul_xyz(t_matrix_3x3 *mat, t_xyz *vec);
t_xyz ft_xyz_mul_mat(t_xyz *vec, t_matrix_3x3 *mat);
t_matrix_3x3 ft_mat_mul(t_matrix_3x3 *mat1, t_matrix_3x3 *mat2);
t_matrix_3x3 ft_mat_transpose(t_matrix_3x3 *mat);

//math.c
t_matrix_3x3 ft_xyz_rotate(t_xyz *vec1, t_xyz *vec2);

//2d_rotate.c
t_matrix_3x3 ft_xy_rotate_ox(float cos_x, float sin_x);
t_matrix_3x3 ft_xy_rotate_oy(float cos_y, float sin_y);
t_matrix_3x3 ft_xy_rotate_oz(float cos_z, float sin_z);


//struct_init_image.c
t_xyz ft_V_init(void);
#endif