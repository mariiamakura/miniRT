/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_coord_vec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 13:10:30 by mparasku          #+#    #+#             */
/*   Updated: 2023/09/08 14:05:27 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

int ft_parse_fov(char *line, float *fov)
{
	char **tab;
	float res;

	tab = ft_split(line, ',');
	res = 0.0;
	if (!tab)
		return (FALSE);
	if (ft_count_arr_elements(tab) != 1)
	{
		ft_free_2d_arr(tab);
		return (FALSE);
	}
	ft_free_2d_arr(tab);
	if (!ft_is_float(line))
		return (FALSE);
	res = ft_str_to_float(line);
	if (res < 0 || res > 180)
		return (FALSE);
	*fov = res;
	return (TRUE);
	
}

int ft_parse_coord(char *line, t_xyz *coord)
{
	char **tab;
	int i;

	i = 0;
	tab = ft_split(line, ',');
	if (!tab)
		return (FALSE);
	if (ft_count_arr_elements(tab) != 3)
	{
		ft_free_2d_arr(tab);
		return (FALSE);
	}
	if (!ft_is_float(tab[0]) || !ft_is_float(tab[1]) || !ft_is_float(tab[2]))
	{
		ft_free_2d_arr(tab);
		return (FALSE);
	}
	coord->x = ft_str_to_float(tab[0]);
	coord->y = ft_str_to_float(tab[1]);
	coord->z = ft_str_to_float(tab[2]);
	ft_free_2d_arr(tab);
	return (TRUE);
}

int ft_parse_vectors(char *line, t_xyz *vectors)
{
	char **tab;
	int i;
	float res;

	i = 0;
	tab = ft_split(line, ',');

	if (!tab)
		return (FALSE);
	if (ft_count_arr_elements(tab) != 3)
	{
		ft_free_2d_arr(tab);
		return (FALSE);
	}
	while (tab[i] && ft_is_float(tab[i]))
	{
		res = ft_str_to_float(tab[i]);
		if (i == 0 && ft_is_range(res))
			vectors->x = res;
		else if (i == 1 && ft_is_range(res))
			vectors->y = res;
		else if (i == 2 && ft_is_range(res))
			vectors->z = res;
		else 
		{
			ft_free_2d_arr(tab);
			return (FALSE);
		}
		i++;
	}
	ft_free_2d_arr(tab);
	return (TRUE);
}

int ft_is_range(float num)
{
	if (num >= -1 && num <= 1)
		return (TRUE);
	return (FALSE);
}