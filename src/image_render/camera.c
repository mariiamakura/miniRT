/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 12:56:57 by mparasku          #+#    #+#             */
/*   Updated: 2023/10/06 17:12:09 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	ft_process_cam_movement(t_rt **rt)
{
	t_xyz			m_dir;
	t_xyz			pos;
	t_matrix_3x3	rot;
	t_xyz			rot_m_dir;

	pos = (*rt)->sc->cam.coord;
	rot = (*rt)->sc->cam.rot;
	if (mlx_is_key_down((*rt)->window->mlx, MLX_KEY_ESCAPE))
		mlx_close_window((*rt)->window->mlx);
	else if (mlx_is_key_down((*rt)->window->mlx, MLX_KEY_W))
		m_dir.z = 1;
	else if (mlx_is_key_down((*rt)->window->mlx, MLX_KEY_S))
		m_dir.z = -1;
	else if (mlx_is_key_down((*rt)->window->mlx, MLX_KEY_D))
		m_dir.x = 1;
	else if (mlx_is_key_down((*rt)->window->mlx, MLX_KEY_A))
		m_dir.x = -1;
	else if (mlx_is_key_down((*rt)->window->mlx, MLX_KEY_SPACE))
		m_dir.y = 1;
	else if (mlx_is_key_down((*rt)->window->mlx, MLX_KEY_LEFT_SHIFT))
		m_dir.y = -1;
	else
		return ;
	rot_m_dir = ft_mat_mul_xyz(&rot, &m_dir);
	(*rt)->sc->cam.coord = ft_xyz_plus(&pos, &rot_m_dir);
}

void	ft_process_cam_rotation(t_rt **rt)
{
	float			rot_val;
	t_matrix_3x3	add_rot;
	t_matrix_3x3	rot;

	rot = (*rt)->sc->cam.rot;
	rot_val = M_PI / 2 / 10;
	if (mlx_is_key_down((*rt)->window->mlx, MLX_KEY_KP_8))
		add_rot = ft_xy_rot_ox(cosf(rot_val), sinf(rot_val));
	else if (mlx_is_key_down((*rt)->window->mlx, MLX_KEY_KP_2))
		add_rot = ft_xy_rot_ox(cosf(-rot_val), sinf(-rot_val));
	else if (mlx_is_key_down((*rt)->window->mlx, MLX_KEY_KP_4))
		add_rot = ft_xy_rot_oy(cosf(-rot_val), sinf(-rot_val));
	else if (mlx_is_key_down((*rt)->window->mlx, MLX_KEY_KP_6))
		add_rot = ft_xy_rot_oy(cosf(rot_val), sinf(rot_val));
	else if (mlx_is_key_down((*rt)->window->mlx, MLX_KEY_KP_7))
		add_rot = ft_xy_rot_oz(cosf(rot_val), sinf(rot_val));
	else if (mlx_is_key_down((*rt)->window->mlx, MLX_KEY_KP_9))
		add_rot = ft_xy_rot_oz(cosf(-rot_val), sinf(-rot_val));
	else
		return ;
	(*rt)->sc->cam.rot = ft_mat_mul(&rot, &add_rot);
}
