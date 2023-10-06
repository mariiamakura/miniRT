/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xy_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:49:16 by mparasku          #+#    #+#             */
/*   Updated: 2023/10/06 14:57:34 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

t_xyz	ft_assign_xyz(t_xy *v)
{
	t_xyz	res;

	res.x = v->x;
	res.y = v->y;
	res.z = 0.0;
	return (res);
}

float	ft_xy_dot(t_xy *v1, t_xy *v2)
{
	t_xyz	v1_xyz;
	t_xyz	v2_xyz;

	v1_xyz = ft_assign_xyz(v1);
	v2_xyz = ft_assign_xyz(v2);
	return (ft_xyz_dot(&v1_xyz, &v2_xyz));
}

t_xyz	ft_xy_mul(t_xy *v1, t_xy *v2)
{
	t_xyz	v1_xyz;
	t_xyz	v2_xyz;

	v1_xyz = ft_assign_xyz(v1);
	v2_xyz = ft_assign_xyz(v2);
	return (ft_xyz_mul(&v1_xyz, &v2_xyz));
}

float	ft_xy_sin(t_xy *v1, t_xy *v2)
{
	float	len1;
	float	len2;
	t_xyz	v12;

	len1 = sqrt(ft_xy_dot(v1, v1));
	len2 = sqrt(ft_xy_dot(v2, v2));
	v12 = ft_xy_mul(v1, v2);
	if (len1 == 0.0 || len2 == 0.0)
		return (0.0);
	return (v12.z / len1 / len2);
}

float	ft_xy_cos(t_xy *v1, t_xy *v2)
{
	float	len1;
	float	len2;
	float	dot;

	len1 = sqrt(ft_xy_dot(v1, v1));
	len2 = sqrt(ft_xy_dot(v2, v2));
	dot = ft_xy_dot(v1, v2);
	if (len1 == 0.0 || len2 == 0.0)
		return (1.0);
	return (dot / len1 / len2);
}
