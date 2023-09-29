
#include "../../include/miniRT.h"

float ft_dot(t_xyz *vec1, t_xyz *vec2) {

    return (vec1->x * vec2->x + vec1->y * vec2->y + vec1->z * vec2->z);
}

float ft_vec_lenght(t_xyz *vec)
{
	float len = sqrt(ft_dot(vec, vec));
	return (len);
}

t_xyz ft_unary_minus(t_xyz *vec) {
    return (t_xyz) {-vec->x, -vec->y, -vec->z};
}

t_xyz ft_vec_multi(t_xyz *vec1, t_xyz *vec2)
{
    t_xyz res;

    res.x = vec1->x * vec2->x;
    res.y = vec1->y * vec2->y;
    res.z = vec1->z * vec2->z;

    return (res);
}


t_xyz ft_vec_mult_float(t_xyz *vec, float i)
{
    t_xyz res;

    res.x = vec->x * i;
    res.y = vec->y * i;
    res.z = vec->z * i;
    return (res);
}

t_xyz ft_plus(t_xyz *vec1, t_xyz *vec2) {
    return (t_xyz) {vec1->x + vec2->x, vec1->y + vec2->y, vec1->z + vec2->z};
}

t_xyz ft_minus(t_xyz *vec1, t_xyz *vec2) {
    return (t_xyz) {vec1->x - vec2->x, vec1->y - vec2->y, vec1->z - vec2->z};
}

t_xyz ft_normalize(t_xyz *vec) {
    float length = sqrt(ft_dot(vec, vec));
    return (t_xyz) {vec->x / length, vec->y / length, vec->z / length};
}