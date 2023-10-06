
#include "../../../include/miniRT.h"

void ft_xy_print(t_xy *vec) {
    printf("vec %f %f\n", vec->x, vec->y);
}

float ft_xy_dot(t_xy *v1, t_xy *v2) {
    t_xyz v1_xyz = {v1->x, v1->y, 0.0};
    t_xyz v2_xyz = {v2->x, v2->y, 0.0};
    return ft_xyz_dot(&v1_xyz, &v2_xyz);
}

t_xyz ft_xy_mul(t_xy *v1, t_xy *v2) {
    t_xyz v1_xyz = {v1->x, v1->y, 0.0};
    t_xyz v2_xyz = {v2->x, v2->y, 0.0};
    return ft_xyz_mul(&v1_xyz, &v2_xyz);
}

float ft_xy_sin(t_xy *v1, t_xy *v2) {
    float len1 = sqrt(ft_xy_dot(v1, v1));
    float len2 = sqrt(ft_xy_dot(v2, v2));
    t_xyz v12 = ft_xy_mul(v1, v2);

    if (len1 == 0.0 || len2 == 0.0)
        return (0.0);

    return v12.z / len1 / len2;
}

float ft_xy_cos(t_xy *v1, t_xy *v2) {
    float len1 = sqrt(ft_xy_dot(v1, v1));
    float len2 = sqrt(ft_xy_dot(v2, v2));
    float dot = ft_xy_dot(v1, v2);

    if (len1 == 0.0 || len2 == 0.0)
        return (1.0);

    return (dot / len1 / len2);
}
