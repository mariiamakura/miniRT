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

//ft_manage_list.c
t_objects *last_obj(t_objects *objs);
void ft_add_obj(t_objects **objs, t_objects *new);

//parse_objects.c
int	ft_parse_objects(char *line, t_rt **rt, int index);

//ft_free.c
void ft_free_rt(t_rt *rt);
void ft_print_all(t_rt *rt);

#endif