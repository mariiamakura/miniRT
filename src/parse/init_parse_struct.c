/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parse_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:51:05 by mparasku          #+#    #+#             */
/*   Updated: 2023/10/06 17:14:21 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	ft_init_parse_rt(t_rt **rt)
{
	*rt = malloc(sizeof(t_rt));
	if (!*rt) 
		return (ft_error("rt struct allocation failed"));
	(*rt)->sc = malloc(sizeof(t_sc));
	if (!(*rt)->sc)
	{
		free(*rt);
		return (ft_error("rt->sc struct allocation failed"));
	}
	(*rt)->sc->ambient.id = NULL;
	(*rt)->sc->cam.id = NULL;
	(*rt)->sc->light.id = NULL;
	(*rt)->sc->objs = NULL;
	(*rt)->window = NULL;
	return (TRUE);
}
