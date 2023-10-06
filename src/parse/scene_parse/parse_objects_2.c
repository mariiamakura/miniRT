/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:07:30 by mparasku          #+#    #+#             */
/*   Updated: 2023/10/06 17:12:09 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

t_objects	*create_object(int type)
{
	t_objects	*new_obj;

	new_obj = malloc(sizeof(t_objects));
	if (!new_obj)
		return (NULL);
	new_obj->type = type;
	new_obj->next = NULL;
	return (new_obj);
}

int	parse_object_parameters(char *line, t_objects *new_obj)
{
	if (new_obj->type == PLANE)
	{
		if (!ft_plane_parse(line, &(new_obj->fig.pl)))
			return (FALSE);
	}
	else if (new_obj->type == SPHERE)
	{
		if (!ft_sphere_parse(line, &(new_obj->fig.sp)))
			return (FALSE);
	}
	else if (new_obj->type == CYLINDER)
	{
		if (!ft_parse_cylinder(line, &(new_obj->fig.cy)))
			return (FALSE);
	}
	return (TRUE);
}

int	ft_parse_objects(char *line, t_rt **rt, int index)
{
	t_objects	*new_obj;

	new_obj = NULL;
	if (ft_strncmp(line, "pl ", 2) == 0)
		new_obj = create_object(PLANE);
	else if (ft_strncmp(line, "sp ", 2) == 0)
		new_obj = create_object(SPHERE);
	else if (ft_strncmp(line, "cy ", 3) == 0)
		new_obj = create_object(CYLINDER);
	if (!new_obj)
		return (FALSE);
	if (!parse_object_parameters(line, new_obj))
	{
		free(new_obj);
		return (ft_error("Invalid object format"));
	}
	new_obj->i = index;
	ft_add_obj(&(*rt)->sc->objs, new_obj);
	return (TRUE);
}
