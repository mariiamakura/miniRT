/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:20:53 by mparasku          #+#    #+#             */
/*   Updated: 2023/10/06 14:48:50 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

t_xyz	ft_mat_mul_xyz(t_matrix_3x3 *mat, t_xyz *vec)
{
	t_xyz	res;

	res.x = mat->data[0][0] * vec->x + mat->data[0][1]
		* vec->y + mat->data[0][2] * vec->z;
	res.y = mat->data[1][0] * vec->x + mat->data[1][1]
		* vec->y + mat->data[1][2] * vec->z;
	res.z = mat->data[2][0] * vec->x + mat->data[2][1]
		* vec->y + mat->data[2][2] * vec->z;
	return (res);
}

t_xyz	ft_xyz_mul_mat(t_xyz *vec, t_matrix_3x3 *mat)
{
	t_xyz	res;

	res.x = mat->data[0][0] * vec->x + mat->data[1][0]
		* vec->y + mat->data[2][0] * vec->z;
	res.y = mat->data[0][1] * vec->x + mat->data[1][1]
		* vec->y + mat->data[2][1] * vec->z;
	res.z = mat->data[0][2] * vec->x + mat->data[1][2]
		* vec->y + mat->data[2][2] * vec->z;
	return (res);
}

t_matrix_3x3	ft_mat_mul(t_matrix_3x3 *mat1, t_matrix_3x3 *mat2)
{
	t_m_rows		a;
	t_m_rows		b;
	t_matrix_3x3	res;

	a = ft_assign_m1_rows(mat1);
	b = ft_assign_m2_rows(mat2);
	res.data[0][0] = ft_xyz_dot(&a.row1, &b.row1);
	res.data[0][1] = ft_xyz_dot(&a.row1, &b.row2);
	res.data[0][2] = ft_xyz_dot(&a.row1, &b.row3);
	res.data[1][0] = ft_xyz_dot(&a.row2, &b.row1);
	res.data[1][1] = ft_xyz_dot(&a.row2, &b.row2);
	res.data[1][2] = ft_xyz_dot(&a.row2, &b.row3);
	res.data[2][0] = ft_xyz_dot(&a.row3, &b.row1);
	res.data[2][1] = ft_xyz_dot(&a.row3, &b.row2);
	res.data[2][2] = ft_xyz_dot(&a.row3, &b.row3);
	return (res);
}

t_matrix_3x3	ft_mat_trnsp(t_matrix_3x3 *mat)
{
	t_matrix_3x3	res;

	res.data[0][0] = mat->data[0][0];
	res.data[0][1] = mat->data[1][0];
	res.data[0][2] = mat->data[2][0];
	res.data[1][0] = mat->data[0][1];
	res.data[1][1] = mat->data[1][1];
	res.data[1][2] = mat->data[2][1];
	res.data[2][0] = mat->data[0][2];
	res.data[2][1] = mat->data[1][2];
	res.data[2][2] = mat->data[2][2];
	return (res);
}
