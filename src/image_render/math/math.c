/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:24:40 by mparasku          #+#    #+#             */
/*   Updated: 2023/10/06 14:15:43 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

t_xy	ft_create_xy(float x, float y)
{
	t_xy	res;

	res.x = x;
	res.y = y;
	return (res);
}

t_matrix_3x3	ft_cos_sin_oy(t_xy *v1, t_xy *v2)
{
	t_matrix_3x3	res;
	float			cos;
	float			sin;

	cos = ft_xy_cos(v1, v2);
	sin = ft_xy_sin(v1, v2);
	res = ft_xy_rot_oy(cos, sin);
	return (res);
}

t_matrix_3x3	ft_cos_sin_ox(t_xy *v1, t_xy *v2)
{
	t_matrix_3x3	res;
	float			cos;
	float			sin;

	cos = ft_xy_cos(v1, v2);
	sin = ft_xy_sin(v1, v2);
	res = ft_xy_rot_ox(cos, sin);
	return (res);
}

t_mat_utils	ft_rot_in_2d(t_xyz *v1, t_xyz *v2)
{
	t_mat_utils	res;

	res.xy_ox = ft_create_xy(1, 0);
	res.xy_oy = ft_create_xy(0, 1);
	res.zx_v1 = ft_create_xy(v1->z, v1->x);
	res.rot_mat_1_oy = ft_cos_sin_oy(&res.zx_v1, &res.xy_ox);
	res.v1_1 = ft_mat_mul_xyz(&res.rot_mat_1_oy, v1);
	res.yz_v1_1 = ft_create_xy(res.v1_1.y, res.v1_1.z);
	res.rot_mat_1_ox = ft_cos_sin_ox(&res.yz_v1_1, &res.xy_oy);
	res.zx_v2 = ft_create_xy(v2->z, v2->x);
	res.rot_mat_2_oy_trnsp = ft_cos_sin_oy(&res.zx_v2, &res.xy_ox);
	res.v2_1 = ft_mat_mul_xyz(&res.rot_mat_2_oy_trnsp, v2);
	res.yz_v2_1 = ft_create_xy(res.v2_1.y, res.v2_1.z);
	res.rot_mat_2_ox_trnsp = ft_cos_sin_ox(&res.yz_v2_1, &res.xy_oy);
	return (res);
}

t_matrix_3x3	ft_xyz_rot(t_xyz *v1, t_xyz *v2)
{
	t_mat_utils		utils;
	t_all_m			all_m;
	t_matrix_3x3	rot_mat;

	utils = ft_rot_in_2d(v1, v2);
	all_m.rot_mat_2_oy = ft_mat_trnsp(&utils.rot_mat_2_oy_trnsp);
	all_m.rot_mat_2_ox = ft_mat_trnsp(&utils.rot_mat_2_ox_trnsp);
	all_m.rot_mat_1 = ft_mat_mul(&utils.rot_mat_1_ox, &utils.rot_mat_1_oy);
	all_m.rot_mat_2 = ft_mat_mul(&all_m.rot_mat_2_oy, &all_m.rot_mat_2_ox);
	rot_mat = ft_mat_mul(&all_m.rot_mat_2, &all_m.rot_mat_1);
	return (rot_mat);
}
