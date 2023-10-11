/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_used.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:09:36 by mparasku          #+#    #+#             */
/*   Updated: 2023/09/26 12:21:58 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/miniRT.h"

//mlx_key_hook((*rt)->window->mlx, ft_key_callback, (*rt));

void ft_key_callback(mlx_key_data_t key_data, void *rt)
{
	t_rt *new_rt;
	new_rt = (t_rt *)rt;

	if (key_data.action == MLX_PRESS && key_data.key == MLX_KEY_ESCAPE)
		mlx_close_window(new_rt->window->mlx);
}

/* void ft_randomize(void* param)
{
	t_rt *rt;

	rt = (t_rt*)param;
	for (uint32_t i = 0; i < rt->window->img->width; ++i)
	{
		for (uint32_t y = 0; y < rt->window->img->height; ++y)
		{
			uint32_t color = ft_pixel(
					rand() % 0xFF, // R
					rand() % 0xFF, // G
					rand() % 0xFF, // B
					rand() % 0xFF  // A
			);
			mlx_put_pixel(rt->window->img, i, y, color);
		}
	}
} */