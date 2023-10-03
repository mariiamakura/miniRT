
#include "../../include/miniRT.h"

t_matrix_3x3 ft_xy_rotate_ox(float cos_x, float sin_x) {
    return (t_matrix_3x3) {
            {
                    {1, 0,     0     },
                    {0, cos_x, -sin_x},
                    {0, sin_x, cos_x }
            }
    };
}

t_matrix_3x3 ft_xy_rotate_oy(float cos_y, float sin_y) {
    return (t_matrix_3x3) {
            {
                    {cos_y,  0, sin_y},
                    {0,      1, 0    },
                    {-sin_y, 0, cos_y}
            }
    };
}

t_matrix_3x3 ft_xy_rotate_oz(float cos_z, float sin_z) {
    return (t_matrix_3x3) {
            {
                    {cos_z, -sin_z, 0},
                    {sin_z, cos_z,  0},
                    {0,     0,      1}
            }
    };
}

t_matrix_3x3 ft_xyz_rotate(t_xyz *vec1, t_xyz *vec2) {
    t_xy xy_OY = {0, 1};

    // Rotation vec1 to OYZ space in XYZ space
    t_xy xy_vec1 = {vec1->x, vec1->y};
    t_matrix_3x3 rotate_mat_1_oz = ft_xy_rotate_oz(
            ft_xy_cos(&xy_vec1, &xy_OY),
            ft_xy_sin(&xy_vec1, &xy_OY)
    );
    t_xyz vec1_1 = ft_mat_mul_xyz(&rotate_mat_1_oz, vec1);

    // Rotation vec1_1 to OZ ray in YZ space
    t_xy yz_vec1_1 = {vec1_1.y, vec1_1.z};
    t_matrix_3x3 rotate_mat_1_ox = ft_xy_rotate_ox(
            // Here, xy_OY is vertical ray in YZ space (OZ in XYZ space)
            ft_xy_cos(&yz_vec1_1, &xy_OY),
            ft_xy_sin(&yz_vec1_1, &xy_OY)
    );

    // Rotation vec2 to OYZ space in XYZ space
    t_xy xy_vec2 = {vec2->x, vec2->y};
    t_matrix_3x3 rotate_mat_2_oz_transpose = ft_xy_rotate_oz(
            ft_xy_cos(&xy_vec2, &xy_OY),
            ft_xy_sin(&xy_vec2, &xy_OY)
    );
    t_xyz vec2_1 = ft_mat_mul_xyz(&rotate_mat_2_oz_transpose, vec2);

    // Rotation vec1_1 to OZ ray in YZ space
    t_xy yz_vec2_1 = {vec2_1.y, vec2_1.z};
    t_matrix_3x3 rotate_mat_2_ox_transpose = ft_xy_rotate_ox(
            // Here, xy_OY is vertical ray in YZ space (OZ in XYZ space)
            ft_xy_cos(&yz_vec2_1, &xy_OY),
            ft_xy_sin(&yz_vec2_1, &xy_OY)
    );

    // the return matrix for vec2 from OZ ray to XYZ space
    t_matrix_3x3 rotate_mat_2_oz = ft_mat_transpose(&rotate_mat_2_oz_transpose);
    t_matrix_3x3 rotate_mat_2_ox = ft_mat_transpose(&rotate_mat_2_ox_transpose);

    t_matrix_3x3 rotate_mat_1 = ft_mat_mul(&rotate_mat_1_ox, &rotate_mat_1_oz); //from vec1
    t_matrix_3x3 rotate_mat_2 = ft_mat_mul(&rotate_mat_2_oz, &rotate_mat_2_ox); //to vec2
    t_matrix_3x3 rotate_mat = ft_mat_mul(&rotate_mat_2, &rotate_mat_1);

//    t_xyz res1 = ft_mat_mul_xyz(&rotate_mat_1_oz, vec1);
//    t_xyz res2 = ft_mat_mul_xyz(&rotate_mat_1_ox, &res1);
//    t_xyz res3 = ft_mat_mul_xyz(&rotate_mat_2_ox, &res2);
//    t_xyz res4 = ft_mat_mul_xyz(&rotate_mat_2_oz, &res3);
//    t_xyz res = ft_mat_mul_xyz(&rotate_mat, vec1);

//    printf("Rotation to OYZ space in XYZ space\n");
//    ft_mat_print(&rotate_mat_1_oz);
//    ft_xyz_print(&res1);
//    printf("Rotation to OZ ray in YZ space\n");
//    ft_mat_print(&rotate_mat_1_ox);
//    ft_xyz_print(&res2);
//    printf("Rotation from OZ ray in YZ space\n");
//    ft_mat_print(&rotate_mat_2_ox);
//    ft_xyz_print(&res3);
//    printf("Rotation from OYZ space in XYZ space\n");
//    ft_mat_print(&rotate_mat_2_oz);
//    ft_xyz_print(&res4);
//    printf("Full rotation\n");
//    ft_mat_print(&rotate_mat);
//    ft_xyz_print(&res);

    return rotate_mat;
}
