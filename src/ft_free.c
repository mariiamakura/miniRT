/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:53:23 by mparasku          #+#    #+#             */
/*   Updated: 2023/10/06 17:14:21 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

static void	ft_free_objects(t_objects *objs)
{
	t_objects	*cur;
	t_objects	*next;

	cur = objs;
	next = NULL;
	while (cur != NULL)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
}

void	ft_free_rt(t_rt *rt)
{
	if (rt != NULL)
	{
		if (rt->sc != NULL)
		{
			if (rt->sc->objs != NULL)
			{
				ft_free_objects(rt->sc->objs);
			}
			free(rt->sc);
		}
		if (rt->window != NULL)
		{
			free(rt->window);
		}
		free(rt);
	}
}

/* 
void ft_print_all(t_rt *rt)
{
    printf("-----ambient-------\n");
    printf("id: %s\n", rt->sc->ambient.id);
    printf("ratio: %f\n", rt->sc->ambient.ratio);
    printf("color r %i\n", rt->sc->ambient.color.r);
    printf("color g %i\n", rt->sc->ambient.color.g);
    printf("color b %i\n", rt->sc->ambient.color.b);
    printf("-----cam-------\n");
    printf("coord x %f \n", rt->sc->cam.coord.x);
    printf("coord y %f \n", rt->sc->cam.coord.y);
    printf("coord z %f \n", rt->sc->cam.coord.z);
    printf("vec x %f \n", rt->sc->cam.vector.x);
    printf("vec y %f \n", rt->sc->cam.vector.y);
    printf("vec z %f \n", rt->sc->cam.vector.z);
    printf("fov %f \n", rt->sc->cam.fov);
    printf("-----light-------\n");
    printf("coord x %f \n", rt->sc->light.coord.x);
    printf("coord y %f \n", rt->sc->light.coord.y);
    printf("coord z %f \n", rt->sc->light.coord.z);
    printf("ratio %f \n", rt->sc->light.ratio);
    t_objects *cur = rt->sc->objs;
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
} */
