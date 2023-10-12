/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init_image.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:15:38 by mparasku          #+#    #+#             */
/*   Updated: 2023/10/04 16:19:04 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_xyz	ft_v_init(void)
{
	t_xyz	v;

	v.x = 0.0;
	v.y = 0.0;
	v.z = 1.0;
	return (v);
}
