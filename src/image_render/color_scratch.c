/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_scratch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:23:58 by mparasku          #+#    #+#             */
/*   Updated: 2023/09/25 17:10:10 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BLACK   0x000000
#define GREEN   0x00FF00
#define YELLOW  0xFFFF00
#define RED     0xFF0000

#include "../../include/miniRT.h"

void ft_gradient(t_rt **rt)
{
   // Calculate color step values
    uint32_t step_r = 255 / WIDTH;
    uint32_t step_g = 255 / HEIGHT;

    // Loop to draw the gradient
	for (uint32_t x = 0; x < (*rt)->window->img->width; ++x)
	{
		for (uint32_t y = 0; y < (*rt)->window->img->height; ++y)
        {
			printf("x: %i\n", x);
            uint32_t color = (x * step_r << 16) | (y * step_g << 8);
            mlx_put_pixel(((*rt)->window->img), x, y, color);
			// color++;
        }
    }
}