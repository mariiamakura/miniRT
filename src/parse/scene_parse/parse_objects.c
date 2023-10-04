/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:06:14 by mparasku          #+#    #+#             */
/*   Updated: 2023/10/04 15:14:04 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

int	ft_plane_parse(char *line, t_plane *pl)
{
	t_plane	plane;
	char	**tab;

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
	if (!ft_parse_coord(tab[1], &plane.coord) 
		|| !ft_parse_vectors(tab[2], &plane.vector)
		|| !ft_parse_color(tab[3], &plane.color))
	{
		ft_free_2d_arr(tab);
		return (FALSE);
	}
	ft_free_2d_arr(tab);
	*pl = plane; 
	return (TRUE);
}

int	ft_sphere_parse(char *line, t_sphere *sp)
{
	t_sphere	sphere;
	char		**tab;

	ft_bzero(&sphere, sizeof(t_sphere));
	tab = ft_split(line, ' ');
	if (!tab)
		return (FALSE);
	if (ft_count_arr_elements(tab) != 4)
	{
		ft_free_2d_arr(tab);
		return (FALSE);
	}
	sphere.id = "sp";
	if (!ft_parse_coord(tab[1], &sphere.coord)
		|| !ft_parse_num_var(tab[2], &sphere.r)
		|| !ft_parse_color(tab[3], &sphere.color))
	{
		ft_free_2d_arr(tab);
		return (FALSE);
	}
	ft_free_2d_arr(tab);
	*sp = sphere;
	return (TRUE);
}

int	ft_parse_cylinder(char *line, t_cylinder *cy)
{
	t_cylinder	cylinder;
	char		**tab;

	ft_bzero(&cylinder, sizeof(t_cylinder));
	tab = ft_split(line, ' ');
	if (!tab)
		return (FALSE);
	if (ft_count_arr_elements(tab) != 6)
	{
		ft_free_2d_arr(tab);
		return (FALSE);
	}
	cylinder.id = "cy";
	if (!ft_parse_coord(tab[1], &cylinder.coord)
		|| !ft_parse_vectors(tab[2], &cylinder.vector) 
		|| !ft_parse_num_var(tab[3], &cylinder.diameter)
		|| !ft_parse_num_var(tab[4], &cylinder.height) 
		|| !ft_parse_color(tab[5], &cylinder.color))
	{
		ft_free_2d_arr(tab);
		return (FALSE);
	}
	ft_free_2d_arr(tab);
	*cy = cylinder;
	return (TRUE);
}

/* int	ft_parse_objects(char *line, t_rt **rt, int index)
{
	t_objects	*new_obj;

	new_obj = malloc(sizeof(t_objects));
	if (!new_obj)
		return (FALSE);
	if (ft_strncmp(line, "pl ", 2) == 0)
	{
		new_obj->type = PLANE;
		if (!ft_plane_parse(line, &(new_obj->fig.pl)))
		ft_objs_error(new_obj)
	}
	else if (ft_strncmp(line, "sp ", 2) == 0)
	{
		new_obj->type = SPHERE;
		if (!ft_sphere_parse(line, &(new_obj->fig.sp)))
		{
			free(new_obj);
			return (ft_error("sp: now a valid format"));
		}
	}
	else if (ft_strncmp(line, "cy ", 3) == 0)
	{
		new_obj->type = CYLINDER;
		if (!ft_parse_cylinder(line, &(new_obj->fig.cy)))
		{
			free(new_obj);
			return (ft_error("cy: now a valid format"));
		}
	}
	new_obj->i = index;
	new_obj->next = NULL;
	ft_add_obj(&(*rt)->scene->objs, new_obj);
	return (TRUE);
} */
