/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:06:14 by mparasku          #+#    #+#             */
/*   Updated: 2023/09/08 18:08:29 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

int ft_plane_parse(char *line, t_plane *pl)
{
	t_plane plane;
	char **tab;
	
	ft_bzero(&plane, sizeof(t_plane));
	tab = ft_split(line, ' ');
	if (!tab)
		return (FALSE);
	if (ft_count_arr_elements(tab) != 4)
	{
		ft_free_2d_arr(tab);
		return (FALSE);
	}
	plane.id = "pl";
	if (!ft_parse_coord(tab[1], &plane.coord) || !ft_parse_vectors(tab[2], &plane.vector)
			|| !ft_parse_color(tab[3], &plane.color))
	{
		ft_free_2d_arr(tab);
		return (FALSE);
	}
	ft_free_2d_arr(tab);
	*pl = plane; 
	return (TRUE);
	
}

int	ft_parse_objects(char *line, t_rt **rt, int index)
{
	t_objects *new_obj;
	
	new_obj = malloc(sizeof(t_objects));
	if (!new_obj)
		return (FALSE);
	if (ft_strncmp(line, "pl ", 2) == 0)
	{
		new_obj->type = PLANE;
		if (!ft_plane_parse(line, &(new_obj->fig.pl)))
		{
			free(new_obj);
			return (ft_error("pl: now a valid format"));
		}
	}
	new_obj->i = index;
	index = index + 1;
	new_obj->next = NULL;
	ft_add_obj(&(*rt)->scene->objs, new_obj);
	printf("id %s\n", new_obj->fig.pl.id);
	printf("%s\n", (*rt)->scene->light.id);
	index++;
	return (TRUE);
}
