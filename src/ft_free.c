/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:53:23 by mparasku          #+#    #+#             */
/*   Updated: 2023/09/25 15:03:36 by mparasku         ###   ########.fr       */
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
		if (rt->window)
		{
			//free(rt->window->mlx);
			//free(rt->window->img);
			free(rt->window);
		}
        free(rt);
    }
}

void ft_print_all(t_rt *rt)
{
	printf("-----ambient-------\n");
	printf("id: %s\n", rt->scene->ambient.id);
	printf("ratio: %f\n", rt->scene->ambient.ratio);
	printf("color r %i\n", rt->scene->ambient.color.r);
	printf("color g %i\n", rt->scene->ambient.color.g);
	printf("color b %i\n", rt->scene->ambient.color.b);
	printf("-----camera-------\n");
    printf("coord ");
    ft_xyz_print(&(rt->scene->camera.coord));
    printf("rotation\n");
    ft_mat_print(&(rt->scene->camera.rotation));
	printf("fov %f \n", rt->scene->camera.fov);
	printf("-----light-------\n");
    printf("coord ");
    ft_xyz_print(&(rt->scene->light.coord));
	printf("ratio %f \n", rt->scene->light.ratio);
	t_objects *cur = rt->scene->objs;
	while (cur)
	{
		if (cur->type == PLANE)
		{
			printf("-----pl-------\n");
			printf("index %i \n", cur->i);
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
		else if (cur->type == SPHERE)
		{
			printf("-----sp-------\n");
			printf("index %i \n", cur->i);
			printf("coord x %f \n",  cur->fig.sp.coord.x);
			printf("coord y %f \n",  cur->fig.sp.coord.y);
			printf("coord z %f \n",  cur->fig.sp.coord.z);
			printf("radius %f \n",  cur->fig.sp.r);
			printf("color r %i\n",  cur->fig.sp.color.r);
			printf("color g %i\n",  cur->fig.sp.color.g);
			printf("color b %i\n",  cur->fig.sp.color.b);
		}
		else if (cur->type == CYLINDER)
		{
			printf("-----cy-------\n");
			printf("index %i \n", cur->i);
			printf("coord x %f \n",  cur->fig.cy.coord.x);
			printf("coord y %f \n",  cur->fig.cy.coord.y);
			printf("coord z %f \n",  cur->fig.cy.coord.z);
			printf("vec x %f \n", cur->fig.cy.vector.x);
			printf("vec y %f \n", cur->fig.cy.vector.y);
			printf("vec z %f \n", cur->fig.cy.vector.z);
			printf("diameter %f \n",  cur->fig.cy.diameter);
			printf("height %f \n",  cur->fig.cy.height);
			printf("color r %i\n",  cur->fig.cy.color.r);
			printf("color g %i\n",  cur->fig.cy.color.g);
			printf("color b %i\n",  cur->fig.cy.color.b);
		}
		cur = cur->next;
	}

}
