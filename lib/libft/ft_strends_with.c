/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strends_with.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:55:47 by mparasku          #+#    #+#             */
/*   Updated: 2023/06/08 17:01:05 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_ends_with(char *str, char *end)
{
	int		end_size;
	int		str_size;
	char	*str_point_to_end;

	end_size = ft_strlen(end);
	str_size = ft_strlen(str);
	str_point_to_end = str + str_size - end_size;
	if (str_size <= end_size)
		return (1);
	return (ft_strncmp(str_point_to_end, end, end_size));
}
