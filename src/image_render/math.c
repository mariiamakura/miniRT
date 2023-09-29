
#include "../../include/miniRT.h"


float ft_2d_dot(t_xy *vec1, t_xy *vec2)
{
    return (vec1->x * vec2->x + vec1->y * vec2->y);
}

float ft_angle(t_xy *vec1, t_xy *vec2)
{
    float len1 = sqrt(ft_2d_dot(vec1, vec1);
    float len2 = sqrt(ft_2d_dot(vec2, vec2);
    float dot = ft_2d_dot(vec1, vec2);

    return (acosf(dot / len1 / len2));
}

float[3][3] ft_matrix_mul(float[3][3] mat1, float[3][3] mat2)
{
    t_xyz mat1_1 = {mat1[0][0], mat1[0][1], mat1[0][2]};
    t_xyz mat1_2 = {mat1[1][0], mat1[1][1], mat1[1][2]};
    t_xyz mat1_3 = {mat1[2][0], mat1[2][1], mat1[2][2]};

    t_xyz mat2_1 = {mat2[0][0], mat2[1][0], mat2[2][0]};
    t_xyz mat2_2 = {mat2[0][1], mat2[1][1], mat2[2][1]};
    t_xyz mat2_3 = {mat2[0][2], mat2[1][2], mat2[2][2]};

    float[3][3] res = {
        {ft_dot(mat1_1, mat2_1), ft_dot(mat1_1, mat2_2), ft_dot(mat1_1, mat2_3)},
        {ft_dot(mat1_2, mat2_1), ft_dot(mat1_2, mat2_2), ft_dot(mat1_2, mat2_3)},
        {ft_dot(mat1_3, mat2_1), ft_dot(mat1_3, mat2_2), ft_dot(mat1_3, mat2_3)}
    };
    return (res);
}

float[3][3] ft_rotate(t_xyz *vec1, t_xyz *vec2)
{
    t_xy vec1_x = {vec1->y, vec1->z};
    t_xy vec2_x = {vec2->y, vec2->z};

    t_xy vec1_y = {vec1->x, vec1->z};
    t_xy vec2_y = {vec2->x, vec2->z};

    t_xy vec1_z = {vec1->x, vec1->y};
    t_xy vec2_z = {vec2->x, vec2->y};


    float angle_x = ft_angle(&vec1_x, &vec2_x); //angle of rotation around x
    float angle_y = ft_angle(&vec1_y, &vec2_y); //angle of rotation around y
    float angle_z = ft_angle(&vec1_z, &vec2_z); //angle of rotation around z

    float[3][3] rotate_matrix_x = {
            {1.0, 0.0, 0.0},
            {0.0, cosf(angle_x), -sinf(angle_x)},
            {0.0, sinf(angle_x), cosf(angle_x)}
    };

    float[3][3] rotate_matrix_y = {
            {cosf(angle_y), 0.0, sinf(angle_y)},
            {0.0, 1.0, 0.0},
            {-sinf(angle_y), 0.0, cosf(angle_y)},
    };

    float[3][3] rotate_matrix_z = {
            {cosf(angle_z), -sinf(angle_z), 0.0},
            {sinf(angle_z), cosf(angel_z), 0.0},
            {0.0, 0.0, 1.0};
    };

    return (ft_matrix_mul(ft_matrix_mul(rotate_matrix_x, rotate_matrix_y), rotate_matrix_z));
}

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