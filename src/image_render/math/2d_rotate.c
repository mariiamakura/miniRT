/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:42:16 by mparasku          #+#    #+#             */
/*   Updated: 2023/10/04 16:44:23 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

t_matrix_3x3	ft_xy_rotate_ox(float cos_x, float sin_x)
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

t_matrix_3x3	ft_xy_rotate_oy(float cos_y, float sin_y)
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

t_matrix_3x3	ft_xy_rotate_oz(float cos_z, float sin_z)
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
