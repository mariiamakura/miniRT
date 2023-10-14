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

void* renderThread(void *arg) {
	ThreadData *data = (ThreadData *)arg;
	t_rt *rt = data->rt;

	for (int y = data->startRow; y < data->endRow; ++y)
	{
		for (int x = 0; x < CW; ++x)
		{
			int cy = CH - y - 1;
			int color = ft_render_fun(&rt, x, cy);
			mlx_put_pixel(rt->window->img, x, y, color);
		}
	}

	return NULL;
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

void render_sc(t_rt **rt)
{
	int numThreads = 4;
	pthread_t threads[numThreads];
	ThreadData threadData[numThreads];

	int rowsPerThread = CH / numThreads;

	for (int i = 0; i < numThreads; ++i)
	{
		threadData[i].rt = *rt;
		threadData[i].startRow = i * rowsPerThread;
		threadData[i].endRow = (i == numThreads - 1) ? CH : (i + 1) * rowsPerThread;
		pthread_create(&threads[i], NULL, renderThread, &threadData[i]);
	}

	for (int i = 0; i < numThreads; ++i)
	{
		pthread_join(threads[i], NULL);
	}
}
