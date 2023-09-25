/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_used.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:09:36 by mparasku          #+#    #+#             */
/*   Updated: 2023/09/25 16:09:53 by mparasku         ###   ########.fr       */
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