/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:24:40 by mparasku          #+#    #+#             */
/*   Updated: 2023/10/06 13:59:21 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

 t_xy ft_create_xy(float x, float y)
 {
	t_xy res;

	res.x = x;
	res.y = y;
	return (res);
 }

t_matrix_3x3 ft_cos_sin_oy(t_xy *vec1, t_xy *vec2)
{
	t_matrix_3x3 res;
	float cos;
	float sin;

	cos = ft_xy_cos(vec1, vec2);
	sin = ft_xy_sin(vec1, vec2);
	res = ft_xy_rotate_oy(cos, sin);
	
	return (res);
}

t_matrix_3x3 ft_cos_sin_ox(t_xy *vec1, t_xy *vec2)
{
	t_matrix_3x3 res;
	float cos;
	float sin;

	cos = ft_xy_cos(vec1, vec2);
	sin = ft_xy_sin(vec1, vec2);
	res = ft_xy_rotate_ox(cos, sin);
	
	return (res);
}


t_mat_utils	ft_rotate_in_2d(t_xyz *vec1, t_xyz *vec2)
{
	t_mat_utils	res;

	res.xy_ox = ft_create_xy(1, 0);
	res.xy_oy = ft_create_xy(0, 1);

	/* The rotation matrix from vec1 in XYZ space to vec1_1 in YZ space */
	res.zx_vec1 = ft_create_xy(vec1->z, vec1->x);
	// Here, xy_ox is first ray in YZ space (OZ in XYZ space)
	res.rotate_mat_1_oy = ft_cos_sin_oy(&res.zx_vec1, &res.xy_ox);
	res.vec1_1 = ft_mat_mul_xyz(&res.rotate_mat_1_oy, vec1);

	// The rotation matrix from vec1_1 in YZ space to vec1_2 in OZ space
	res.yz_vec1_1 = ft_create_xy(res.vec1_1.y, res.vec1_1.z);
	// Here, xy_oy is second ray in YZ space (OZ in XYZ space)
	res.rotate_mat_1_ox = ft_cos_sin_ox(&res.yz_vec1_1,&res.xy_oy);

	// The rotation matrix from vec2 in XYZ space to vec2_1 in YZ space
	res.zx_vec2 = ft_create_xy(vec2->z, vec2->x);
	// Here, xy_ox is first ray in YZ space (OZ in XYZ space)
	res.rotate_mat_2_oy_transpose = ft_cos_sin_oy(&res.zx_vec2, &res.xy_ox);
	res.vec2_1 = ft_mat_mul_xyz(&res.rotate_mat_2_oy_transpose, vec2);

	// The rotation matrix from vec2_1 in YZ space to vec2_2 in OZ space
	res.yz_vec2_1 = ft_create_xy(res.vec2_1.y, res.vec2_1.z);
	// Here, xy_oy is second ray in YZ space (OZ in XYZ space)
	res.rotate_mat_2_ox_transpose = ft_cos_sin_ox(&res.yz_vec2_1, &res.xy_oy);

	return (res);
}

t_matrix_3x3	ft_xyz_rotate(t_xyz *vec1, t_xyz *vec2)
{
	t_mat_utils	utils;
	t_all_m		all_m;

	utils = ft_rotate_in_2d(vec1, vec2);

	// The conversion of the rotation matrices
	// from matrices for rotation from vec2 in XYZ space to intermediate vector in OZ space
	// to matrices for rotation from intermediate vector in OZ space to vec2 in XYZ space
	all_m.rotate_mat_2_oy = ft_mat_transpose(&utils.rotate_mat_2_oy_transpose);
	all_m.rotate_mat_2_ox = ft_mat_transpose(&utils.rotate_mat_2_ox_transpose);

	// The rotation matrix from vec1 in XYZ space to intermediate vector in OZ space
	all_m.rotate_mat_1 = ft_mat_mul(&utils.rotate_mat_1_ox, &utils.rotate_mat_1_oy);
	// The rotation matrix from intermediate vector in OZ space to vec2 in XYZ space
	all_m.rotate_mat_2 = ft_mat_mul(&all_m.rotate_mat_2_oy, &all_m.rotate_mat_2_ox);
	// The rotation matrix from vec1 to vec2 in XYZ space
	t_matrix_3x3 rotate_mat = ft_mat_mul(&all_m.rotate_mat_2, &all_m.rotate_mat_1);

	return rotate_mat;
}