
#include "../../include/miniRT.h"

void ft_print_matrix(t_matrix_3x3 *mat)
{
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++)
            printf("%f ", mat->matrix_3x3[i][j]);
        printf("\n");
    }
}

void ft_print_xyz(t_xyz *vec)
{
    printf("vec %f %f %f\n", vec->x, vec->y, vec->z);
}

void ft_print_xy(t_xy *vec)
{
    printf("vec %f %f\n", vec->x, vec->y);
}

float ft_2d_dot(t_xy *vec1, t_xy *vec2)
{
    return (vec1->x * vec2->x + vec1->y * vec2->y);
}

t_xyz ft_mul_xyz(t_xyz *vec1, t_xyz *vec2)
{
    t_xyz res;

    res.x = vec1->y * vec2->z - vec1->z * vec2->y;
    res.y = vec1->z * vec2->x - vec1->x * vec2->z;
    res.z = vec1->x * vec2->y - vec1->y * vec2->x;

    return (res);
}

t_xyz ft_mul_xy(t_xy *vec1, t_xy *vec2)
{
    t_xyz vec1_xyz = {vec1->x, vec1->y, 0.0};
    t_xyz vec2_xyz = {vec2->x, vec2->y, 0.0};
    t_xyz res = ft_mul_xyz(&vec1_xyz, &vec2_xyz);
    return (res);
}

float ft_sin_xy(t_xy *vec1, t_xy *vec2)
{
    float len1 = sqrt(ft_2d_dot(vec1, vec1));
    float len2 = sqrt(ft_2d_dot(vec2, vec2));
    t_xyz vec12 = ft_mul_xy(vec1, vec2);

    if (len1 == 0.0 || len2 == 0.0)
        return (0.0);

    return vec12.z / len1 / len2;
}

float ft_cos_xy(t_xy *vec1, t_xy *vec2)
{
    float len1 = sqrt(ft_2d_dot(vec1, vec1));
    float len2 = sqrt(ft_2d_dot(vec2, vec2));
    float dot = ft_2d_dot(vec1, vec2);

    if (len1 == 0.0 || len2 == 0.0)
        return (1.0);

    return (dot / len1 / len2);
}

t_xyz ft_mul_mat_xyz(t_matrix_3x3 *mat, t_xyz *vec)
{
	t_xyz res;

	res.x = mat->matrix_3x3[0][0] * vec->x + mat->matrix_3x3[0][1] * vec->y + mat->matrix_3x3[0][2] * vec->z;
	res.y = mat->matrix_3x3[1][0] * vec->x + mat->matrix_3x3[1][1] * vec->y + mat->matrix_3x3[1][2] * vec->z;
	res.z = mat->matrix_3x3[2][0] * vec->x + mat->matrix_3x3[2][1] * vec->y + mat->matrix_3x3[2][2] * vec->z;

	return (res);
}
t_xyz ft_mul_xyz_mat(t_xyz *vec, t_matrix_3x3 *mat)
{
    t_xyz res;

    res.x = mat->matrix_3x3[0][0] * vec->x + mat->matrix_3x3[1][0] * vec->y + mat->matrix_3x3[2][0] * vec->z;
    res.y = mat->matrix_3x3[0][1] * vec->x + mat->matrix_3x3[1][1] * vec->y + mat->matrix_3x3[2][1] * vec->z;
    res.z = mat->matrix_3x3[0][2] * vec->x + mat->matrix_3x3[1][2] * vec->y + mat->matrix_3x3[2][2] * vec->z;

    return (res);
}

t_matrix_3x3 ft_matrix_mul(t_matrix_3x3 mat1, t_matrix_3x3 mat2)
{
    t_xyz mat1_1 = {mat1.matrix_3x3[0][0], mat1.matrix_3x3[0][1], mat1.matrix_3x3[0][2]};
    t_xyz mat1_2 = {mat1.matrix_3x3[1][0], mat1.matrix_3x3[1][1], mat1.matrix_3x3[1][2]};
    t_xyz mat1_3 = {mat1.matrix_3x3[2][0], mat1.matrix_3x3[2][1], mat1.matrix_3x3[2][2]};

    t_xyz mat2_1 = {mat2.matrix_3x3[0][0], mat2.matrix_3x3[1][0], mat2.matrix_3x3[2][0]};
    t_xyz mat2_2 = {mat2.matrix_3x3[0][1], mat2.matrix_3x3[1][1], mat2.matrix_3x3[2][1]};
    t_xyz mat2_3 = {mat2.matrix_3x3[0][2], mat2.matrix_3x3[1][2], mat2.matrix_3x3[2][2]};

    t_matrix_3x3 res = {
		{
        {ft_dot(&mat1_1, &mat2_1), ft_dot(&mat1_1, &mat2_2), ft_dot(&mat1_1, &mat2_3)},
        {ft_dot(&mat1_2, &mat2_1), ft_dot(&mat1_2, &mat2_2), ft_dot(&mat1_2, &mat2_3)},
        {ft_dot(&mat1_3, &mat2_1), ft_dot(&mat1_3, &mat2_2), ft_dot(&mat1_3, &mat2_3)}
		}
    };
    return (res);
}

t_matrix_3x3 ft_rotate(t_xyz *vec1, t_xyz *vec2)
{
    t_xy vec1_x = {vec1->y, vec1->z};
    t_xy vec2_x = {vec2->y, vec2->z};

    t_xy vec1_y = {vec1->z, vec1->x};
    t_xy vec2_y = {vec2->z, vec2->x};

    t_xy vec1_z = {vec1->x, vec1->y};
    t_xy vec2_z = {vec2->x, vec2->y};

    float cos_x = ft_cos_xy(&vec1_x, &vec2_x);
    float cos_y = ft_cos_xy(&vec1_y, &vec2_y);
    float cos_z = ft_cos_xy(&vec1_z, &vec2_z);
    float sin_x = ft_sin_xy(&vec1_x, &vec2_x);
    float sin_y = ft_sin_xy(&vec1_y, &vec2_y);
    float sin_z = ft_sin_xy(&vec1_z, &vec2_z);
    //printf("cos %f %f %f\n", cos_x, cos_y, cos_z);
    //printf("sin %f %f %f\n", sin_x, sin_y, sin_z);

    t_matrix_3x3 rotate_matrix_x = {
		{
            {1.0, 0.0, 0.0},
            {0.0, cos_x, -sin_x},
            {0.0, sin_x, cos_x}
		}
    };

    t_matrix_3x3 rotate_matrix_y = {
		{
            {cos_y, 0.0, sin_y},
            {0.0, 1.0, 0.0},
            {-sin_y, 0.0, cos_y}
		}
    };

    t_matrix_3x3 rotate_matrix_z = {
		{
            {cos_z, -sin_z, 0.0},
            {sin_z, cos_z, 0.0},
            {0.0, 0.0, 1.0}
		}
    };

    t_matrix_3x3 rotate_matrix_xy = ft_matrix_mul(rotate_matrix_x, rotate_matrix_y);
    t_matrix_3x3 rotate_matrix_xyz = ft_matrix_mul(rotate_matrix_xy, rotate_matrix_z);
//
//    t_xyz res;
//    printf("rotate-x\n");
//    ft_print_matrix(&rotate_matrix_x);
//    res = ft_mul_mat_xyz(&rotate_matrix_x, vec1);
//    ft_print_xyz(&res);
//    printf("rotate-y\n");
//    ft_print_matrix(&rotate_matrix_y);
//    res = ft_mul_mat_xyz(&rotate_matrix_y, vec1);
//    ft_print_xyz(&res);
//    printf("rotate-z\n");
//    ft_print_matrix(&rotate_matrix_z);
//    res = ft_mul_mat_xyz(&rotate_matrix_z, vec1);
//    ft_print_xyz(&res);
//    printf("rotate-xy\n");
//    ft_print_matrix(&rotate_matrix_xy);
//    res = ft_mul_mat_xyz(&rotate_matrix_xy, vec1);
//    ft_print_xyz(&res);
//    printf("rotate-xyz\n");
//    ft_print_matrix(&rotate_matrix_xyz);
//    res = ft_mul_mat_xyz(&rotate_matrix_xyz, vec1);
//    ft_print_xyz(&res);

    return rotate_matrix_xyz;
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