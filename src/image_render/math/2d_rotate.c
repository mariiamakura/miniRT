/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_rot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:42:16 by mparasku          #+#    #+#             */
/*   Updated: 2023/10/04 16:44:23 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

t_matrix_3x3	ft_xy_rot_ox(float cos_x, float sin_x)
{
	t_matrix_3x3	res;

	res.data[0][0] = 1;
	res.data[0][1] = 0;
	res.data[0][2] = 0;
	res.data[1][0] = 0;
	res.data[1][1] = cos_x;
	res.data[1][2] = -sin_x;
	res.data[2][0] = 0;
	res.data[2][1] = sin_x;
	res.data[2][2] = cos_x;
	return (res);
}

t_matrix_3x3	ft_xy_rot_oy(float cos_y, float sin_y)
{
	t_matrix_3x3	res;

	res.data[0][0] = cos_y;
	res.data[0][1] = 0;
	res.data[0][2] = sin_y;
	res.data[1][0] = 0;
	res.data[1][1] = 1;
	res.data[1][2] = 0;
	res.data[2][0] = -sin_y;
	res.data[2][1] = 0;
	res.data[2][2] = cos_y;
	return (res);
}

t_matrix_3x3	ft_xy_rot_oz(float cos_z, float sin_z)
{
	t_matrix_3x3	res;

	res.data[0][0] = cos_z;
	res.data[0][1] = -sin_z;
	res.data[0][2] = 0;
	res.data[1][0] = sin_z;
	res.data[1][1] = cos_z;
	res.data[1][2] = 0;
	res.data[2][0] = 0;
	res.data[2][1] = 0;
	res.data[2][2] = 1;
	return (res);
}

t_m_rows	ft_assign_m1_rows(t_matrix_3x3 *mat)
{
	t_m_rows	res;

	res.row1.x = mat->data[0][0];
	res.row1.y = mat->data[0][1];
	res.row1.z = mat->data[0][2];
	res.row2.x = mat->data[1][0];
	res.row2.y = mat->data[1][1];
	res.row2.z = mat->data[1][2];
	res.row3.x = mat->data[2][0];
	res.row3.y = mat->data[2][1];
	res.row3.z = mat->data[2][2];
	return (res);
}

t_m_rows	ft_assign_m2_rows(t_matrix_3x3 *mat)
{
	t_m_rows	res;

	res.row1.x = mat->data[0][0];
	res.row1.y = mat->data[1][0];
	res.row1.z = mat->data[2][0];
	res.row2.x = mat->data[0][1];
	res.row2.y = mat->data[1][1];
	res.row2.z = mat->data[2][1];
	res.row3.x = mat->data[0][2];
	res.row3.y = mat->data[1][2];
	res.row3.z = mat->data[2][2];
	return (res);
}
