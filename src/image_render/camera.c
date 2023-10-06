/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 12:56:57 by mparasku          #+#    #+#             */
/*   Updated: 2023/10/06 17:03:27 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void ft_process_camera_movement(t_rt **rt)
{
	t_xyz move_direction;
	float move_value;

	move_value = 1;
	if (mlx_is_key_down((*rt)->window->mlx, MLX_KEY_ESCAPE))
		mlx_close_window((*rt)->window->mlx);
	else if (mlx_is_key_down((*rt)->window->mlx, MLX_KEY_W))
		move_direction.z = move_value;
	else if (mlx_is_key_down((*rt)->window->mlx, MLX_KEY_S))
		move_direction.z = -move_value;
	else if (mlx_is_key_down((*rt)->window->mlx, MLX_KEY_D))
		move_direction.x = move_value;
	else if (mlx_is_key_down((*rt)->window->mlx, MLX_KEY_A))
		move_direction.x = -move_value;
	else if (mlx_is_key_down((*rt)->window->mlx, MLX_KEY_SPACE))
		move_direction.y = move_value;
	else if (mlx_is_key_down((*rt)->window->mlx, MLX_KEY_LEFT_SHIFT))
		move_direction.y = -move_value;
	else
		return;

	t_xyz position = (*rt)->scene->camera.coord;
	t_matrix_3x3 rotation = (*rt)->scene->camera.rot;
	t_xyz rotated_move_direction = ft_mat_mul_xyz(&rotation, &move_direction);
	(*rt)->scene->camera.coord = ft_xyz_plus(&position, &rotated_move_direction);
}

void ft_process_camera_rotation(t_rt **rt)
{
	float rotation_value = M_PI / 2 / 10;
	t_matrix_3x3 additional_rotation;

	if (mlx_is_key_down((*rt)->window->mlx, MLX_KEY_KP_8))
		additional_rotation = ft_xy_rot_ox(
				cosf(rotation_value),
				sinf(rotation_value)
		);
	else if (mlx_is_key_down((*rt)->window->mlx, MLX_KEY_KP_2))
		additional_rotation = ft_xy_rot_ox(
				cosf(-rotation_value),
				sinf(-rotation_value)
		);
	else if (mlx_is_key_down((*rt)->window->mlx, MLX_KEY_KP_4))
		additional_rotation = ft_xy_rot_oy(
				cosf(-rotation_value),
				sinf(-rotation_value)
		);
	else if (mlx_is_key_down((*rt)->window->mlx, MLX_KEY_KP_6))
		additional_rotation = ft_xy_rot_oy(
				cosf(rotation_value),
				sinf(rotation_value)
		);
	else if (mlx_is_key_down((*rt)->window->mlx, MLX_KEY_KP_7))
		additional_rotation = ft_xy_rot_oz(
				cosf(rotation_value),
				sinf(rotation_value)
		);
	else if (mlx_is_key_down((*rt)->window->mlx, MLX_KEY_KP_9))
		additional_rotation = ft_xy_rot_oz(
				cosf(-rotation_value),
				sinf(-rotation_value)
		);
	else
		return;

	t_matrix_3x3 rotation = (*rt)->scene->camera.rot;
	(*rt)->scene->camera.rot = ft_mat_mul(&rotation, &additional_rotation);
}