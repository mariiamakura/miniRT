/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   'RenderFun.c'                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaron  <lbaron@student.42berlin.de>       :+:  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023-10-12 17:09:54 by lbaron            :+:    #+#             */
/*   Updated: 2023-10-12 17:09:54 by lbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

static void	*render_thread(void *arg)
{
	t_thread_data	*data;
	t_rt			*rt;
	int				x;
	int				y;
	int				color;

	data = (t_thread_data *)arg;
	rt = data->rt;
	y = data->start_row;
	while (y < data->end_row)
	{
		x = 0;
		while (x < CW)
		{
			color = ft_render_fun(&rt, x, CH - y - 1);
			mlx_put_pixel(rt->window->img, x, y, color);
			x++;
		}
		y++;
	}
	return (NULL);
}

void	create_threads(pthread_t *threads,
			t_thread_data *thread_data,
			t_rt **rt, int rows_per_thread)
{
	int	i;

	i = 0;
	while (i < NUM_THREADS)
	{
		thread_data[i].rt = *rt;
		thread_data[i].start_row = i * rows_per_thread;
		if (i == NUM_THREADS - 1)
			thread_data[i].end_row = CH;
		else
			thread_data[i].end_row = (i + 1) * rows_per_thread;
		pthread_create(&threads[i], NULL, render_thread, &thread_data[i]);
		i++;
	}
}

static void	join_threads(pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < NUM_THREADS)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

int	ft_render_fun(t_rt **rt, int Cx, int Cy)
{
	t_xyz			o;
	t_matrix_3x3	rot;
	t_xyz			can_to_v;
	t_xyz			d;
	t_color			color;

	o = (*rt)->sc->cam.coord;
	rot = (*rt)->sc->cam.rot;
	can_to_v = ft_can_to_vport(Cx, Cy, (*rt)->sc->cam.fov);
	d = ft_mat_mul_xyz(&rot, &can_to_v);
	color = trace_ray(rt, &o, &d);
	return (ft_pixel(color.r, color.g, color.b, 255));
}

void	render_sc(t_rt **rt)
{
	pthread_t		threads[NUM_THREADS];
	t_thread_data	thread_data[NUM_THREADS];
	int				rows_per_thread;

	rows_per_thread = CH / NUM_THREADS;
	create_threads(threads, thread_data, rt, rows_per_thread);
	join_threads(threads);
}
