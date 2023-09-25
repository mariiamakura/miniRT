/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:50:17 by mparasku          #+#    #+#             */
/*   Updated: 2023/09/25 11:54:11 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int ft_parse(char *file, t_rt **rt)
{
	int index;
	int fd;

	index = 0;
	if (!ft_file_validation(file))
		return (FALSE);
	if (!ft_init_parse_rt(rt))
		return (FALSE);
	fd = open(file, O_RDONLY);
	if(!ft_fill_structs(fd, rt, index))
	{
		close (fd);
		return (FALSE);
	}
	close(fd);
	return (TRUE);
}

int	ft_fill_structs(int fd, t_rt **rt, int index)
{
	char *line;
	int error_flag;

	line = get_next_line(fd);
	error_flag = FALSE;
	while (line)
	{
		if (ft_strncmp(line, "A ", 2) == 0)
		{
			if (!ft_ambient_light_parse(line, rt))
				error_flag = TRUE;
		}
		else if (ft_strncmp(line, "C ", 2) == 0)
		{
			if (!ft_camera_parse(line, rt))
				error_flag = TRUE;
		}
		else if (ft_strncmp(line, "L ", 2) == 0)
		{
			if (!ft_light_parse(line, rt))
				error_flag = TRUE;
		}
		else if (ft_strncmp(line, "pl ", 2) == 0 || ft_strncmp(line, "sp ", 2) == 0
               || ft_strncmp(line, "cy ", 2) == 0)
		{
			if (!ft_parse_objects(line, rt, index))
				error_flag = TRUE;
			index++;
		}
		free (line);
		line = get_next_line(fd);
	}
	free (line);
	if (error_flag == TRUE)
		return (FALSE);
	return (TRUE);
}

int	ft_file_validation(char *file)
{
	char *file_str;
	
	if (ft_check_extention(file) == FALSE)
		return (FALSE);
	file_str = ft_file_to_str(file);
	if (!file_str)
		return (FALSE);
	if (file_str[0] == '\0')
	{
		free(file_str);
		return (ft_error("File is empty"));
	}
	free(file_str);
	return (TRUE);
}


