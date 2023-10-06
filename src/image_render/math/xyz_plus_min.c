/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xyz_plus_min.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:05:54 by mparasku          #+#    #+#             */
/*   Updated: 2023/10/06 15:14:53 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

float	ft_xyz_length(t_xyz *vec)
{
	float	len;

	len = sqrt(ft_xyz_dot(vec, vec));
	return (len);
}

t_xyz	ft_xyz_unary_minus(t_xyz *vec)
{
	t_xyz	res;

	res.x = -vec->x;
	res.y = -vec->y;
	res.z = -vec->z;
	return (res);
}

t_xyz	ft_xyz_plus(t_xyz *v1, t_xyz *v2)
{
	t_xyz	res;

	res.x = v1->x + v2->x;
	res.y = v1->y + v2->y;
	res.z = v1->z + v2->z;
	return (res);
}

t_xyz	ft_xyz_minus(t_xyz *v1, t_xyz *v2)
{
	t_xyz	res;

	res.x = v1->x - v2->x;
	res.y = v1->y - v2->y;
	res.z = v1->z - v2->z;
	return (res);
}
