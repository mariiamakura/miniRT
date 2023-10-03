
#include "../../include/miniRT.h"

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
    float cos_x = ft_xy_cos(&vec1_x, &vec2_x);
    float sin_x = ft_xy_sin(&vec1_x, &vec2_x);
    t_matrix_3x3 rotate_matrix_x = ft_rotate_x(cos_x, sin_x);
    res = ft_mat_mul_xyz(&rotate_matrix_x, &res);

    t_xy vec1_y = {res.z, res.x};
    t_xy vec2_y = {vec2->z, vec2->x};
    float cos_y = ft_xy_cos(&vec1_y, &vec2_y);
    float sin_y = ft_xy_sin(&vec1_y, &vec2_y);
    t_matrix_3x3 rotate_matrix_y = ft_rotate_y(cos_y, sin_y);
    res = ft_mat_mul_xyz(&rotate_matrix_y, &res);

    t_xy vec1_z = {res.x, res.y};
    t_xy vec2_z = {vec2->x, vec2->y};
    float cos_z = ft_xy_cos(&vec1_z, &vec2_z);
    float sin_z = ft_xy_sin(&vec1_z, &vec2_z);
    t_matrix_3x3 rotate_matrix_z = ft_rotate_z(cos_z, sin_z);
    res = ft_mat_mul_xyz(&rotate_matrix_z, &res);

    t_matrix_3x3 rotate_matrix_xy = ft_mat_mul(&rotate_matrix_y, &rotate_matrix_x);
    t_matrix_3x3 rotate_matrix_xyz = ft_mat_mul(&rotate_matrix_z, &rotate_matrix_xy);

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
