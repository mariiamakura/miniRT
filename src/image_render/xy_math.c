
#include "../../include/miniRT.h"

void ft_xy_print(t_xy *vec) {
    printf("vec %f %f\n", vec->x, vec->y);
}

float ft_xy_dot(t_xy *vec1, t_xy *vec2) {
    return (vec1->x * vec2->x + vec1->y * vec2->y);
}

t_xyz ft_xy_mul(t_xy *vec1, t_xy *vec2) {
    t_xyz vec1_xyz = {vec1->x, vec1->y, 0.0};
    t_xyz vec2_xyz = {vec2->x, vec2->y, 0.0};
    t_xyz res = ft_xyz_mul(&vec1_xyz, &vec2_xyz);
    return (res);
}

float ft_xy_sin(t_xy *vec1, t_xy *vec2) {
    float len1 = sqrt(ft_xy_dot(vec1, vec1));
    float len2 = sqrt(ft_xy_dot(vec2, vec2));
    t_xyz vec12 = ft_xy_mul(vec1, vec2);

    if (len1 == 0.0 || len2 == 0.0)
        return (0.0);

    return vec12.z / len1 / len2;
}

float ft_xy_cos(t_xy *vec1, t_xy *vec2) {
    float len1 = sqrt(ft_xy_dot(vec1, vec1));
    float len2 = sqrt(ft_xy_dot(vec2, vec2));
    float dot = ft_xy_dot(vec1, vec2);

    if (len1 == 0.0 || len2 == 0.0)
        return (1.0);

    return (dot / len1 / len2);
}
