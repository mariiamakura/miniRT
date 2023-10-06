
#include "../../../include/miniRT.h"

void ft_xyz_print(t_xyz *vec) {
    printf("vec %f %f %f\n", vec->x, vec->y, vec->z);
}

float ft_xyz_dot(t_xyz *v1, t_xyz *v2) {

    return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

float ft_xyz_length(t_xyz *vec) {
    float len = sqrt(ft_xyz_dot(vec, vec));
    return (len);
}

t_xyz ft_xyz_unary_minus(t_xyz *vec) {
    return (t_xyz) {-vec->x, -vec->y, -vec->z};
}

t_xyz ft_xyz_mul(t_xyz *v1, t_xyz *v2) {
    t_xyz res;

    res.x = v1->y * v2->z - v1->z * v2->y;
    res.y = v1->z * v2->x - v1->x * v2->z;
    res.z = v1->x * v2->y - v1->y * v2->x;

    return (res);
}

t_xyz ft_xyz_elm_mul(t_xyz *v1, t_xyz *v2) {
    t_xyz res;

    res.x = v1->x * v2->x;
    res.y = v1->y * v2->y;
    res.z = v1->z * v2->z;

    return (res);
}

t_xyz ft_xyz_mul_num(t_xyz *vec, float i) {
    t_xyz res;

    res.x = vec->x * i;
    res.y = vec->y * i;
    res.z = vec->z * i;
    return (res);
}

t_xyz ft_xyz_plus(t_xyz *v1, t_xyz *v2) {
    return (t_xyz) {v1->x + v2->x, v1->y + v2->y, v1->z + v2->z};
}

t_xyz ft_xyz_minus(t_xyz *v1, t_xyz *v2) {
    return (t_xyz) {v1->x - v2->x, v1->y - v2->y, v1->z - v2->z};
}

t_xyz ft_xyz_normalize(t_xyz *vec) {
    float length = sqrt(ft_xyz_dot(vec, vec));
    return (t_xyz) {vec->x / length, vec->y / length, vec->z / length};
}
