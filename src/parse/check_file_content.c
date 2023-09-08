/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_content.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:44:52 by mparasku          #+#    #+#             */
/*   Updated: 2023/09/06 13:15:07 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

char *ft_file_to_str(char *file)
{
	int fd;
	char *file_str;
	char *line;
	
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_error("File opening failed");
		close(fd);
		return (NULL);
	}
	file_str = ft_calloc(1, 1);
	if (!file_str)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		file_str = ft_strjoin(file_str, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	free (line);
	return (file_str);
}

int ft_check_extention(char *file)
{
	if (ft_str_ends_with(file, ".rt") != 0)
	{
		return(ft_error("Wrong extention"));
	}
	return (TRUE);
}
