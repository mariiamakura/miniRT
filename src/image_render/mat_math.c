
#include "../../include/miniRT.h"

void ft_mat_print(t_matrix_3x3 *mat) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            printf("%f ", mat->matrix_3x3[i][j]);
        printf("\n");
    }
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
