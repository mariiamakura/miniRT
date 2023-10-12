/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_cam_parse.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:56:54 by mparasku          #+#    #+#             */
/*   Updated: 2023/10/06 17:12:09 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

int	ft_ambient_light_parse(char *line, t_rt **rt)
{
	char		**tab;
	t_ambient	amb;

	if ((*rt)->sc->ambient.id)
		return (ft_error("More then 1 ambient light"));
	tab = ft_split(line, ' ');
	if (!tab)
		return (ft_error("Ambient tab malloc failed"));
	if (ft_count_arr_elements(tab) != 3)
	{
		ft_free_2d_arr(tab);
		return (ft_error("A: wrong number of arguments"));
	}
	ft_bzero(&amb, sizeof(t_ambient));
	amb.id = "A";
	if (!ft_parse_ratio(tab[1], &amb.ratio) 
		|| !ft_parse_color(tab[2], &amb.color))
	{
		ft_free_2d_arr(tab);
		return (ft_error("A: not valid format"));
	}
	(*rt)->sc->ambient = amb;
	ft_free_2d_arr(tab);
	return (TRUE);
}

int	ft_cam_parse(char *line, t_rt **rt)
{
	t_cam	cam;
	char	**tab;
	t_xyz	v;

	if ((*rt)->sc->cam.id)
		return (ft_error("More then 1 cam"));
	tab = ft_split(line, ' ');
	if (!tab)
		return (ft_error("cam malloc failed"));
	ft_bzero(&cam, sizeof(t_cam));
	cam.id = "C";
	if (ft_count_arr_elements(tab) != 4
		|| !ft_parse_coord(tab[1], &cam.coord)
		|| !ft_parse_vectors(tab[2], &cam.vector)
		|| !ft_parse_fov(tab[3], &cam.fov))
	{
		ft_free_2d_arr(tab);
		return (ft_error("C: not valid format"));
	}
	v = ft_v_init();
	cam.rot = ft_xyz_rot(&v, &cam.vector);
	(*rt)->sc->cam = cam;
	ft_free_2d_arr(tab);
	return (TRUE);
}

int	ft_light_parse(char *line, t_rt **rt)
{
	t_light		light;
	char		**tab;

	if ((*rt)->sc->light.id)
		return (ft_error("More then 1 light"));
	tab = ft_split(line, ' ');
	if (!tab)
		return (ft_error("Light malloc failed"));
	if (ft_count_arr_elements(tab) != 3)
	{
		ft_free_2d_arr(tab);
		return (ft_error("L: wrong number of arguments"));
	}
	ft_bzero(&light, sizeof(t_light));
	light.id = "L";
	if (!ft_parse_coord(tab[1], &light.coord) 
		|| !ft_parse_ratio(tab[2], &light.ratio))
	{
		ft_free_2d_arr(tab);
		return (ft_error("L: not valid format"));
	}
	(*rt)->sc->light = light;
	ft_free_2d_arr(tab);
	return (TRUE);
}
