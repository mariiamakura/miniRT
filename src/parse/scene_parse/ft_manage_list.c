/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 18:05:02 by mparasku          #+#    #+#             */
/*   Updated: 2023/09/08 18:07:05 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

t_objects *last_obj(t_objects *objs)
{
	if (!objs)
		return (NULL);
	while (objs->next)
		objs = objs->next;
	return (objs);
}

void ft_add_obj(t_objects **objs, t_objects *new)
{
	t_objects *last;

	if (!new)
		return ;
	if (!*objs)
	{
		*objs = new;
		return ;
	}
	last = last_obj(*objs);
	last->next = new;
}
