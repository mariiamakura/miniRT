/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parse_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:51:05 by mparasku          #+#    #+#             */
/*   Updated: 2023/09/06 16:51:07 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int ft_init_parse_rt(t_rt **rt)
{
	*rt = malloc(sizeof(t_rt));
	if (!*rt) 
		return (ft_error("rt struct allocation failed"));
	(*rt)->scene = malloc(sizeof(t_scene));
	if (!(*rt)->scene)
	{
		free(*rt);
		return (ft_error("rt->scene struct allocation failed"));
	}
	(*rt)->scene->ambient.id = NULL;
	(*rt)->scene->camera.id = NULL;
	(*rt)->scene->light.id = NULL;
	return (TRUE);
}

