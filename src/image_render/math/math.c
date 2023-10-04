/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:24:40 by mparasku          #+#    #+#             */
/*   Updated: 2023/10/04 16:42:38 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

t_matrix_3x3 ft_xyz_rotate(t_xyz *vec1, t_xyz *vec2) {
    t_xy xy_OX = {1, 0};
    t_xy xy_OY = {0, 1};

    // The rotation matrix from vec1 in XYZ space to vec1_1 in YZ space
    t_xy zx_vec1 = {vec1->z, vec1->x};
    t_matrix_3x3 rotate_mat_1_oy = ft_xy_rotate_oy(
            // Here, xy_OX is first ray in YZ space (OZ in XYZ space)
            ft_xy_cos(&zx_vec1, &xy_OX),
            ft_xy_sin(&zx_vec1, &xy_OX)
    );
    t_xyz vec1_1 = ft_mat_mul_xyz(&rotate_mat_1_oy, vec1);

    // The rotation matrix from vec1_1 in YZ space to vec1_2 in OZ space
    t_xy yz_vec1_1 = {vec1_1.y, vec1_1.z};
    t_matrix_3x3 rotate_mat_1_ox = ft_xy_rotate_ox(
            // Here, xy_OY is second ray in YZ space (OZ in XYZ space)
            ft_xy_cos(&yz_vec1_1, &xy_OY),
            ft_xy_sin(&yz_vec1_1, &xy_OY)
    );

    // The rotation matrix from vec2 in XYZ space to vec2_1 in YZ space
    t_xy zx_vec2 = {vec2->z, vec2->x};
    t_matrix_3x3 rotate_mat_2_oy_transpose = ft_xy_rotate_oy(
            // Here, xy_OX is first ray in YZ space (OZ in XYZ space)
            ft_xy_cos(&zx_vec2, &xy_OX),
            ft_xy_sin(&zx_vec2, &xy_OX)
    );
    t_xyz vec2_1 = ft_mat_mul_xyz(&rotate_mat_2_oy_transpose, vec2);

    // The rotation matrix from vec2_1 in YZ space to vec2_2 in OZ space
    t_xy yz_vec2_1 = {vec2_1.y, vec2_1.z};
    t_matrix_3x3 rotate_mat_2_ox_transpose = ft_xy_rotate_ox(
            // Here, xy_OY is second ray in YZ space (OZ in XYZ space)
            ft_xy_cos(&yz_vec2_1, &xy_OY),
            ft_xy_sin(&yz_vec2_1, &xy_OY)
    );

    // The conversion of the rotation matrices
    // from matrices for rotation from vec2 in XYZ space to intermediate vector in OZ space
    // to matrices for rotation from intermediate vector in OZ space to vec2 in XYZ space
    t_matrix_3x3 rotate_mat_2_oy = ft_mat_transpose(&rotate_mat_2_oy_transpose);
    t_matrix_3x3 rotate_mat_2_ox = ft_mat_transpose(&rotate_mat_2_ox_transpose);

    // The rotation matrix from vec1 in XYZ space to intermediate vector in OZ space
    t_matrix_3x3 rotate_mat_1 = ft_mat_mul(&rotate_mat_1_ox, &rotate_mat_1_oy);
    // The rotation matrix from intermediate vector in OZ space to vec2 in XYZ space
    t_matrix_3x3 rotate_mat_2 = ft_mat_mul(&rotate_mat_2_oy, &rotate_mat_2_ox);
    // The rotation matrix from vec1 to vec2 in XYZ space
    t_matrix_3x3 rotate_mat = ft_mat_mul(&rotate_mat_2, &rotate_mat_1);
	
    return rotate_mat;
}
