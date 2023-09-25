/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imag_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:39:27 by mparasku          #+#    #+#             */
/*   Updated: 2023/09/25 15:37:56 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int ft_imag_init(t_rt **rt)
{
	(*rt)->window = malloc(sizeof(t_window));
	if (!(*rt)->window)
		return(ft_error("mlx error"));
	(*rt)->window->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!(*rt)->window->mlx)
		return(ft_error("mlx error"));
	(*rt)->window->img = mlx_new_image((*rt)->window->mlx, WIDTH, HEIGHT);
	if (!(*rt)->window->img)
	{
		mlx_close_window((*rt)->window->mlx);
		return(ft_error("img error"));
	}
	if (mlx_image_to_window((*rt)->window->mlx, (*rt)->window->img, 0, 0) == -1)
	{
		mlx_close_window((*rt)->window->mlx);
		return(ft_error("img error"));
	}
	mlx_key_hook((*rt)->window->mlx, ft_key_callback, (*rt));
	mlx_loop((*rt)->window->mlx);
	return (TRUE);
}

void ft_key_callback(mlx_key_data_t key_data, void *rt)
{
	t_rt *new_rt;
	new_rt = (t_rt *)rt;

	if (key_data.action == MLX_PRESS && key_data.key == MLX_KEY_ESCAPE)
		mlx_close_window(new_rt->window->mlx);
}