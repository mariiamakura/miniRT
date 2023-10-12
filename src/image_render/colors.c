/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   'colors.c'                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaron  <lbaron@student.42berlin.de>       :+:  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023-10-12 15:09:13 by lbaron            :+:    #+#             */
/*   Updated: 2023-10-12 15:09:13 by lbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

//void ft_gradient(t_color *color, t_rt **rt)
//{
//	for (int x = 0; x < CW; x++) {
//		for (int y = 0; y < CH; y++) {
//			//printf("Scanlines remaining: %i\n", Ch - y);
//			float r = (float)x / (CW - 1);
//			float g = 0;
//			float b = (float)y / (CH - 1);
//			int ir = (int)(color->r * r);
//			int ig = (int)(color->g * g);
//			int ib = (int)(color->b * b);
//			mlx_put_pixel((*rt)->window->img, x, y, ft_pixel(ir, ig, ib, 255));
//		}
//	}
//}
//
//void	ft_put_pixel(int x, int y, int color, t_rt **rt)
//{
//	int	can_x;
//	int	can_y;
//
//	can_x = x + CW / 2;
//	can_y = y + CH / 2;
//	if (can_x >= 0 && can_x < CW && can_y >= 0 && can_y < CH)
//		mlx_put_pixel((*rt)->window->img, can_x, can_y, color);
//}

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

t_color	ft_set_fin_color(t_color *origin, float i)
{
	t_color	fin_color;

	fin_color.r = origin->r * i;
	fin_color.g = origin->g * i;
	fin_color.b = origin->b * i;
	fin_color.r = fminf(fmaxf(fin_color.r, 0), 255);
	fin_color.g = fminf(fmaxf(fin_color.g, 0), 255);
	fin_color.b = fminf(fmaxf(fin_color.b, 0), 255);
	return (fin_color);
}
