/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:53:23 by mparasku          #+#    #+#             */
/*   Updated: 2023/09/25 11:27:18 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

static void ft_free_objects(t_objects *objs)
{
	t_objects *cur = objs;
	t_objects *next = NULL;
	while (cur != NULL)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
}


void ft_free_rt(t_rt *rt)
{
    if (rt)
    {
		if (rt->scene->objs)
			ft_free_objects(rt->scene->objs);
        if (rt->scene)
        {
            free(rt->scene);
        }
        free(rt);
    }
}

void ft_print_all(t_rt *rt)
{
/* 	printf("-----ambient-------\n");
	printf("id: %s\n", rt->scene->ambient.id);
	printf("ratio: %f\n", rt->scene->ambient.ratio);
	printf("color r %i\n", rt->scene->ambient.color.r);
	printf("color g %i\n", rt->scene->ambient.color.g);
	printf("color b %i\n", rt->scene->ambient.color.b);
	printf("-----camera-------\n");
	printf("coord x %f \n", rt->scene->camera.coord.x);
	printf("coord y %f \n", rt->scene->camera.coord.y);
	printf("coord z %f \n", rt->scene->camera.coord.z);
	printf("vec x %f \n", rt->scene->camera.vector.x);
	printf("vec y %f \n", rt->scene->camera.vector.y);
	printf("vec z %f \n", rt->scene->camera.vector.z);
	printf("fov %f \n", rt->scene->camera.fov);
	printf("-----light-------\n");
	printf("coord x %f \n", rt->scene->light.coord.x);
	printf("coord y %f \n", rt->scene->light.coord.y);
	printf("coord z %f \n", rt->scene->light.coord.z);
	printf("ratio %f \n", rt->scene->light.ratio); */
	t_objects *cur = rt->scene->objs;
	while (cur)
	{
		if (cur->type == PLANE)
		{
			printf("-----pl-------\n");
			printf("coord x %f \n", cur->fig.pl.coord.x);
			printf("coord y %f \n", cur->fig.pl.coord.y);
			printf("coord z %f \n", cur->fig.pl.coord.z);
			printf("vec x %f \n", cur->fig.pl.vector.x);
			printf("vec y %f \n", cur->fig.pl.vector.y);
			printf("vec z %f \n", cur->fig.pl.vector.z);
			printf("color r %i\n", cur->fig.pl.color.r);
			printf("color g %i\n", cur->fig.pl.color.g);
			printf("color b %i\n", cur->fig.pl.color.b);
		}
		cur = cur->next;
	}
    // printf("-----sp-------\n");
    // printf("coord x %f \n", rt->scene->objs->fig.sp.coord.x);
    // printf("coord y %f \n", rt->scene->objs->fig.sp.coord.y);
    // printf("coord z %f \n", rt->scene->objs->fig.sp.coord.z);
    // printf("radius %f \n", rt->scene->objs->fig.sp.r);
    // printf("color r %i\n", rt->scene->objs->fig.sp.color.r);
    // printf("color g %i\n", rt->scene->objs->fig.sp.color.g);
    // printf("color b %i\n", rt->scene->objs->fig.sp.color.b);
}
