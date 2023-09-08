/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:03:28 by mparasku          #+#    #+#             */
/*   Updated: 2023/06/08 17:02:37 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free(char *str)
{
	free(str);
	return (0);
}

char	*remove_line(char *buf_start)
{
	int		i;
	int		j;
	char	*new_buf;

	i = 0;
	j = 0;
	if (!buf_start)
		return (0);
	while (buf_start[i] && buf_start[i] != '\n')
		i++;
	if (!buf_start[i])
		return (ft_free(buf_start));
	if (buf_start[i] == '\n')
		i++;
	new_buf = (char *)malloc((ft_strlen(buf_start) - i + 1) * sizeof(char));
	if (!new_buf)
		return (0);
	while (buf_start[i + j])
	{
		new_buf[j] = buf_start[i + j];
		j++;
	}
	new_buf[j] = '\0';
	free (buf_start);
	return (new_buf);
}

char	*read_line(char *buf_start)
{
	int		i;
	char	*line;

	i = 0;
	if (!buf_start[i])
		return (0);
	while (buf_start[i] && buf_start[i] != '\n')
		i++;
	if (buf_start[i] == '\n')
		i++;
	line = (char *)malloc((i + 1) * sizeof(char));
	if (!line)
		return (0);
	i = 0;
	while (buf_start[i] && buf_start[i] != '\n')
	{
		line[i] = buf_start[i];
		i++;
	}
	if (buf_start[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*read_buf(int fd, char *buf_start)
{
	char	*buff;
	int		fd_read;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	fd_read = 1;
	while (!ft_strchr(buf_start, '\n') && fd_read != 0)
	{
		fd_read = read(fd, buff, BUFFER_SIZE);
		if (fd_read < 0)
		{
			free (buf_start);
			free(buff);
			return (NULL);
		}
		buff[fd_read] = '\0';
		buf_start = ft_strjoin(buf_start, buff);
	}
	free(buff);
	return (buf_start);
}

char	*get_next_line(int fd)
{
	char		*temp;
	static char	*buf_start;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buf_start = read_buf(fd, buf_start);
	if (!buf_start)
		return (NULL);
	temp = read_line(buf_start);
	buf_start = remove_line(buf_start);
	return (temp);
}

/* int main()
{
	int	fd;
	char *str;
	
	fd = open("empty.txt", O_RDWR);
	
	str = get_next_line(fd);
	printf("%s", str);
	free (str);

	str = get_next_line(fd);
	printf("%s", str);
	free (str);
	
	str = get_next_line(fd);
	printf("%s", str);
	free (str);
	
	str = get_next_line(fd);
	printf("%s", str);
	free (str);
	close (fd);
} */

/* to see leaks
valgrind -s --leak-check=full --show-leak-kinds=all 
--track-origins=yes ./a.out */ 