/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_camera_parse.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:56:54 by mparasku          #+#    #+#             */
/*   Updated: 2023/09/08 14:43:43 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

int	ft_ambient_light_parse(char *line, t_rt **rt)
{
	int i;
	char **tab;
	t_ambient amb;

	i = 1;
	if ((*rt)->scene->ambient.id)
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
	if (!ft_parse_ratio(tab[1], &amb.ratio) || !ft_parse_color(tab[2], &amb.color))
	{
		ft_free_2d_arr(tab);
		return (ft_error("A: not valid format"));
	}
	(*rt)->scene->ambient = amb;
	ft_free_2d_arr(tab);
	return (TRUE);
}

int ft_camera_parse(char *line, t_rt **rt)
{
	t_camera camera;
	char **tab;
	int i;

	i = 0;
	if ((*rt)->scene->camera.id)
		return (ft_error("More then 1 camera"));
	tab = ft_split(line, ' ');
	if (!tab)
		return (ft_error("Camera malloc failed"));
	if (ft_count_arr_elements(tab) != 4)
	{
		ft_free_2d_arr(tab);
		return (ft_error("C: wrong number of arguments"));
	}
	ft_bzero(&camera, sizeof(t_camera));
	camera.id = "C";
	if (!ft_parse_coord(tab[1], &camera.coord) || !ft_parse_vectors(tab[2], &camera.vector)
			|| !ft_parse_fov(tab[3], &camera.fov))
	{
		ft_free_2d_arr(tab);
		return (ft_error("C: not valid format"));
	}
	(*rt)->scene->camera = camera; 
	ft_free_2d_arr(tab);
	return (TRUE);
}


int ft_light_parse(char *line, t_rt **rt)
{
	t_light light;
	char **tab;
	int i;

	i = 0;
	if ((*rt)->scene->light.id)
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
	if (!ft_parse_coord(tab[1], &light.coord) || !ft_parse_ratio(tab[2], &light.ratio))
	{
		ft_free_2d_arr(tab);
		return (ft_error("L: not valid format"));
	}
	(*rt)->scene->light = light; 
	ft_free_2d_arr(tab);
	return (TRUE);
}

