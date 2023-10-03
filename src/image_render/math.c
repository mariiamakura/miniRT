
#include "../../include/miniRT.h"

void ft_mat_print(t_matrix_3x3 *mat) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            printf("%f ", mat->matrix_3x3[i][j]);
        printf("\n");
    }
}

void ft_xyz_print(t_xyz *vec) {
    printf("vec %f %f %f\n", vec->x, vec->y, vec->z);
}

void ft_xy_print(t_xy *vec) {
    printf("vec %f %f\n", vec->x, vec->y);
}

float ft_xy_dot(t_xy *vec1, t_xy *vec2) {
    return (vec1->x * vec2->x + vec1->y * vec2->y);
}

t_xyz ft_xyz_mul(t_xyz *vec1, t_xyz *vec2) {
    t_xyz res;

    res.x = vec1->y * vec2->z - vec1->z * vec2->y;
    res.y = vec1->z * vec2->x - vec1->x * vec2->z;
    res.z = vec1->x * vec2->y - vec1->y * vec2->x;

    return (res);
}

t_xyz ft_xy_mul(t_xy *vec1, t_xy *vec2) {
    t_xyz vec1_xyz = {vec1->x, vec1->y, 0.0};
    t_xyz vec2_xyz = {vec2->x, vec2->y, 0.0};
    t_xyz res = ft_xyz_mul(&vec1_xyz, &vec2_xyz);
    return (res);
}

float ft_sin_xy(t_xy *vec1, t_xy *vec2) {
    float len1 = sqrt(ft_xy_dot(vec1, vec1));
    float len2 = sqrt(ft_xy_dot(vec2, vec2));
    t_xyz vec12 = ft_xy_mul(vec1, vec2);

    if (len1 == 0.0 || len2 == 0.0)
        return (0.0);

    return vec12.z / len1 / len2;
}

float ft_cos_xy(t_xy *vec1, t_xy *vec2) {
    float len1 = sqrt(ft_xy_dot(vec1, vec1));
    float len2 = sqrt(ft_xy_dot(vec2, vec2));
    float dot = ft_xy_dot(vec1, vec2);

    if (len1 == 0.0 || len2 == 0.0)
        return (1.0);

    return (dot / len1 / len2);
}

t_xyz ft_mat_mul_xyz(t_matrix_3x3 *mat, t_xyz *vec) {
    t_xyz res;

    res.x = mat->matrix_3x3[0][0] * vec->x + mat->matrix_3x3[0][1] * vec->y + mat->matrix_3x3[0][2] * vec->z;
    res.y = mat->matrix_3x3[1][0] * vec->x + mat->matrix_3x3[1][1] * vec->y + mat->matrix_3x3[1][2] * vec->z;
    res.z = mat->matrix_3x3[2][0] * vec->x + mat->matrix_3x3[2][1] * vec->y + mat->matrix_3x3[2][2] * vec->z;

    return (res);
}

t_xyz ft_xyz_mul_mat(t_xyz *vec, t_matrix_3x3 *mat) {
    t_xyz res;

    res.x = mat->matrix_3x3[0][0] * vec->x + mat->matrix_3x3[1][0] * vec->y + mat->matrix_3x3[2][0] * vec->z;
    res.y = mat->matrix_3x3[0][1] * vec->x + mat->matrix_3x3[1][1] * vec->y + mat->matrix_3x3[2][1] * vec->z;
    res.z = mat->matrix_3x3[0][2] * vec->x + mat->matrix_3x3[1][2] * vec->y + mat->matrix_3x3[2][2] * vec->z;

    return (res);
}

t_matrix_3x3 ft_mat_mul(t_matrix_3x3 mat1, t_matrix_3x3 mat2) {
    t_xyz mat1_1 = {mat1.matrix_3x3[0][0], mat1.matrix_3x3[0][1], mat1.matrix_3x3[0][2]};
    t_xyz mat1_2 = {mat1.matrix_3x3[1][0], mat1.matrix_3x3[1][1], mat1.matrix_3x3[1][2]};
    t_xyz mat1_3 = {mat1.matrix_3x3[2][0], mat1.matrix_3x3[2][1], mat1.matrix_3x3[2][2]};

    t_xyz mat2_1 = {mat2.matrix_3x3[0][0], mat2.matrix_3x3[1][0], mat2.matrix_3x3[2][0]};
    t_xyz mat2_2 = {mat2.matrix_3x3[0][1], mat2.matrix_3x3[1][1], mat2.matrix_3x3[2][1]};
    t_xyz mat2_3 = {mat2.matrix_3x3[0][2], mat2.matrix_3x3[1][2], mat2.matrix_3x3[2][2]};

    t_matrix_3x3 res = {
            {
                    {ft_xyz_dot(&mat1_1, &mat2_1), ft_xyz_dot(&mat1_1, &mat2_2), ft_xyz_dot(&mat1_1, &mat2_3)},
                    {ft_xyz_dot(&mat1_2, &mat2_1), ft_xyz_dot(&mat1_2, &mat2_2), ft_xyz_dot(&mat1_2, &mat2_3)},
                    {ft_xyz_dot(&mat1_3, &mat2_1), ft_xyz_dot(&mat1_3, &mat2_2), ft_xyz_dot(&mat1_3, &mat2_3)}
            }
    };
    return (res);
}

t_matrix_3x3 ft_rotate_x(float cos_x, float sin_x) {
    return (t_matrix_3x3) {
            {
                    {1.0, 0.0, 0.0},
                    {0.0, cos_x, -sin_x},
                    {0.0, sin_x, cos_x}
            }
    };
}

t_matrix_3x3 ft_rotate_y(float cos_y, float sin_y) {
    return (t_matrix_3x3) {
            {
                    {cos_y, 0.0, sin_y},
                    {0.0, 1.0, 0.0},
                    {-sin_y, 0.0, cos_y}
            }
    };
}

t_matrix_3x3 ft_rotate_z(float cos_z, float sin_z) {
    return (t_matrix_3x3) {
            {
                    {cos_z, -sin_z, 0.0},
                    {sin_z, cos_z, 0.0},
                    {0.0, 0.0, 1.0}
            }
    };
}

t_matrix_3x3 ft_rotate(t_xyz *vec1, t_xyz *vec2) {
    t_xyz res = *vec1;

    t_xy vec1_x = {res.y, res.z};
    t_xy vec2_x = {vec2->y, vec2->z};
    float cos_x = ft_cos_xy(&vec1_x, &vec2_x);
    float sin_x = ft_sin_xy(&vec1_x, &vec2_x);
    t_matrix_3x3 rotate_matrix_x = ft_rotate_x(cos_x, sin_x);
    res = ft_mat_mul_xyz(&rotate_matrix_x, &res);

    t_xy vec1_y = {res.z, res.x};
    t_xy vec2_y = {vec2->z, vec2->x};
    float cos_y = ft_cos_xy(&vec1_y, &vec2_y);
    float sin_y = ft_sin_xy(&vec1_y, &vec2_y);
    t_matrix_3x3 rotate_matrix_y = ft_rotate_y(cos_y, sin_y);
    res = ft_mat_mul_xyz(&rotate_matrix_y, &res);

    t_xy vec1_z = {res.x, res.y};
    t_xy vec2_z = {vec2->x, vec2->y};
    float cos_z = ft_cos_xy(&vec1_z, &vec2_z);
    float sin_z = ft_sin_xy(&vec1_z, &vec2_z);
    t_matrix_3x3 rotate_matrix_z = ft_rotate_z(cos_z, sin_z);
    res = ft_mat_mul_xyz(&rotate_matrix_z, &res);

    t_matrix_3x3 rotate_matrix_xy = ft_mat_mul(rotate_matrix_y, rotate_matrix_x);
    t_matrix_3x3 rotate_matrix_xyz = ft_mat_mul(rotate_matrix_z, rotate_matrix_xy);

//    t_xyz res1 = ft_mat_mul_xyz(&rotate_matrix_z, vec1);
//    t_xyz res2 = ft_mat_mul_xyz(&rotate_matrix_z, &res1);
//    t_xyz res3 = ft_mat_mul_xyz(&rotate_matrix_z, &res2);
//    t_xyz res4 = ft_mat_mul_xyz(&rotate_matrix_xy, vec1);
//    t_xyz res5 = ft_mat_mul_xyz(&rotate_matrix_xyz, vec1);
//
//    printf("rotate-1(x)\n");
//    ft_mat_print(&rotate_matrix_x);
//    ft_xyz_print(&res1);
//    printf("rotate-2(xy)\n");
//    ft_mat_print(&rotate_matrix_y);
//    ft_xyz_print(&res2);
//    printf("rotate-3(xyz)\n");
//    ft_mat_print(&rotate_matrix_z);
//    ft_xyz_print(&res3);
//    printf("rotate-4(xy)\n");
//    ft_mat_print(&rotate_matrix_xy);
//    ft_xyz_print(&res4);
//    printf("rotate-5(xyz)\n");
//    ft_mat_print(&rotate_matrix_xyz);
//    ft_xyz_print(&res5);

    return rotate_matrix_xyz;
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