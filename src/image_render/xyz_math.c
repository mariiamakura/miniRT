
#include "../../include/miniRT.h"

void ft_xyz_print(t_xyz *vec) {
    printf("vec %f %f %f\n", vec->x, vec->y, vec->z);
}

float ft_xyz_dot(t_xyz *vec1, t_xyz *vec2) {

    return (vec1->x * vec2->x + vec1->y * vec2->y + vec1->z * vec2->z);
}

float ft_xyz_length(t_xyz *vec) {
    float len = sqrt(ft_xyz_dot(vec, vec));
    return (len);
}

t_xyz ft_xyz_unary_minus(t_xyz *vec) {
    return (t_xyz) {-vec->x, -vec->y, -vec->z};
}

t_xyz ft_xyz_mul(t_xyz *vec1, t_xyz *vec2) {
    t_xyz res;

    res.x = vec1->y * vec2->z - vec1->z * vec2->y;
    res.y = vec1->z * vec2->x - vec1->x * vec2->z;
    res.z = vec1->x * vec2->y - vec1->y * vec2->x;

    return (res);
}

t_xyz ft_xyz_elm_mul(t_xyz *vec1, t_xyz *vec2) {
    t_xyz res;

    res.x = vec1->x * vec2->x;
    res.y = vec1->y * vec2->y;
    res.z = vec1->z * vec2->z;

    return (res);
}

t_xyz ft_xyz_mul_num(t_xyz *vec, float i) {
    t_xyz res;

    res.x = vec->x * i;
    res.y = vec->y * i;
    res.z = vec->z * i;
    return (res);
}

t_xyz ft_xyz_plus(t_xyz *vec1, t_xyz *vec2) {
    return (t_xyz) {vec1->x + vec2->x, vec1->y + vec2->y, vec1->z + vec2->z};
}

t_xyz ft_xyz_minus(t_xyz *vec1, t_xyz *vec2) {
    return (t_xyz) {vec1->x - vec2->x, vec1->y - vec2->y, vec1->z - vec2->z};
}

t_xyz ft_xyz_normalize(t_xyz *vec) {
    float length = sqrt(ft_xyz_dot(vec, vec));
    return (t_xyz) {vec->x / length, vec->y / length, vec->z / length};
}