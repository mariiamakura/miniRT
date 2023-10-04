/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 18:05:02 by mparasku          #+#    #+#             */
/*   Updated: 2023/10/04 15:45:43 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

t_objects	*last_obj(t_objects *objs)
{
	if (!objs)
		return (NULL);
	while (objs->next)
		objs = objs->next;
	return (objs);
}

void	ft_add_obj(t_objects **objs, t_objects *new)
{
	t_objects	*last;

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

int	ft_is_range(float num)
{
	if (num >= -1 && num <= 1)
		return (TRUE);
	return (FALSE);
}

int	ft_parse_ratio(char *str, float *ratio)
{
	if (ft_is_float(str) == FALSE)
		return (FALSE);
	*ratio = ft_str_to_float(str);
	if (*ratio < 0 || *ratio > 1)
		return (FALSE);
	return (TRUE);
}
