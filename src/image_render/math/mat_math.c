
#include "../../../include/miniRT.h"

void ft_mat_print(t_matrix_3x3 *mat) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            printf("%f ", mat->data[i][j]);
        printf("\n");
    }
}

t_xyz ft_mat_mul_xyz(t_matrix_3x3 *mat, t_xyz *vec) {
    t_xyz res;

    res.x = mat->data[0][0] * vec->x + mat->data[0][1] * vec->y + mat->data[0][2] * vec->z;
    res.y = mat->data[1][0] * vec->x + mat->data[1][1] * vec->y + mat->data[1][2] * vec->z;
    res.z = mat->data[2][0] * vec->x + mat->data[2][1] * vec->y + mat->data[2][2] * vec->z;

    return (res);
}

t_xyz ft_xyz_mul_mat(t_xyz *vec, t_matrix_3x3 *mat) {
    t_xyz res;

    res.x = mat->data[0][0] * vec->x + mat->data[1][0] * vec->y + mat->data[2][0] * vec->z;
    res.y = mat->data[0][1] * vec->x + mat->data[1][1] * vec->y + mat->data[2][1] * vec->z;
    res.z = mat->data[0][2] * vec->x + mat->data[1][2] * vec->y + mat->data[2][2] * vec->z;

    return (res);
}

t_matrix_3x3 ft_mat_mul(t_matrix_3x3 *mat1, t_matrix_3x3 *mat2) {
    t_xyz mat1_1 = {mat1->data[0][0], mat1->data[0][1], mat1->data[0][2]};
    t_xyz mat1_2 = {mat1->data[1][0], mat1->data[1][1], mat1->data[1][2]};
    t_xyz mat1_3 = {mat1->data[2][0], mat1->data[2][1], mat1->data[2][2]};

    t_xyz mat2_1 = {mat2->data[0][0], mat2->data[1][0], mat2->data[2][0]};
    t_xyz mat2_2 = {mat2->data[0][1], mat2->data[1][1], mat2->data[2][1]};
    t_xyz mat2_3 = {mat2->data[0][2], mat2->data[1][2], mat2->data[2][2]};

    t_matrix_3x3 res = {
            {
                    {ft_xyz_dot(&mat1_1, &mat2_1), ft_xyz_dot(&mat1_1, &mat2_2), ft_xyz_dot(&mat1_1, &mat2_3)},
                    {ft_xyz_dot(&mat1_2, &mat2_1), ft_xyz_dot(&mat1_2, &mat2_2), ft_xyz_dot(&mat1_2, &mat2_3)},
                    {ft_xyz_dot(&mat1_3, &mat2_1), ft_xyz_dot(&mat1_3, &mat2_2), ft_xyz_dot(&mat1_3, &mat2_3)}
            }
    };
    return (res);
}

t_matrix_3x3 ft_mat_trnsp(t_matrix_3x3 *mat) {
    return (t_matrix_3x3) {
            {
                    {mat->data[0][0], mat->data[1][0], mat->data[2][0]},
                    {mat->data[0][1], mat->data[1][1], mat->data[2][1]},
                    {mat->data[0][2], mat->data[1][2], mat->data[2][2]}
            }
    };
}
