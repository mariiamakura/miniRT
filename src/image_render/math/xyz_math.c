/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xyz_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:04:48 by mparasku          #+#    #+#             */
/*   Updated: 2023/10/06 15:11:40 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

float	ft_xyz_dot(t_xyz *v1, t_xyz *v2)
{
	float	res;

	res = v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
	return (res);
}

t_xyz	ft_xyz_mul(t_xyz *v1, t_xyz *v2)
{
	t_xyz	res;

	res.x = v1->y * v2->z - v1->z * v2->y;
	res.y = v1->z * v2->x - v1->x * v2->z;
	res.z = v1->x * v2->y - v1->y * v2->x;
	return (res);
}

t_xyz	ft_xyz_elm_mul(t_xyz *v1, t_xyz *v2)
{
	t_xyz	res;

	res.x = v1->x * v2->x;
	res.y = v1->y * v2->y;
	res.z = v1->z * v2->z;
	return (res);
}

t_xyz	ft_xyz_mul_num(t_xyz *vec, float i)
{
	t_xyz	res;

	res.x = vec->x * i;
	res.y = vec->y * i;
	res.z = vec->z * i;
	return (res);
}

t_xyz	ft_xyz_normalize(t_xyz *vec)
{
	float	length;
	t_xyz	res;

	length = sqrt(ft_xyz_dot(vec, vec));
	res.x = vec->x / length;
	res.y = vec->y / length;
	res.z = vec->z / length;
	return (res);
}
