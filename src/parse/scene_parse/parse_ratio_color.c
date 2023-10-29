/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ratio_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:07:54 by mparasku          #+#    #+#             */
/*   Updated: 2023/10/04 15:45:29 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

int	ft_parse_color(char *str, t_color *colors)
{
	char	**color;

	color = ft_split(str, ',');
	if (!color)
		return (FALSE);
	if (ft_count_arr_elements(color) != 3)
	{
		ft_free_2d_arr(color);
		return (FALSE);
	}
	if (!is_color(color[0]) || !is_color(color[1]) || !is_color(color[2]))
	{
		ft_free_2d_arr(color);
		return (FALSE);
	}
	colors->r = ft_atoi(color[0]);
	colors->g = ft_atoi(color[1]);
	colors->b = ft_atoi(color[2]);
	ft_free_2d_arr(color);
	return (TRUE);
}

int	is_color(char *str)
{
	int	i;
	int	color;

	i = 0;
	if (!str)
		return (FALSE);
	if (str[0] == '\0' || str[0] == '\n' || str[0] == ' ')
		return (FALSE);
	while (str[i])
	{
		if (str[i] != '\n' && str[i] != ' ' && !ft_isdigit(str[i]))
			return (FALSE);
		i++;
	}
	color = ft_atoi(str);
	if (color >= 0 && color <= 255)
		return (TRUE);
	else
		return (FALSE);
}

float	ft_str_to_float(char *str)
{
	float	res;
	float	after_dot;
	float	div;
	float	sign;

	sign = 1.0;
	div = 1.0;
	after_dot = 0.0;
	if (str && str[0] == '-')
		sign *= -1.0;
	res = (float)ft_atoi(str);
	while (*str && *str != '.')
		str++;
	if (*str++ == '.')
	{
		while (*str >= '0' && *str <= '9')
		{
			div *= 10.0;
			after_dot += (*str - '0') / div;
			str++;
		}
		res += after_dot * sign;
	}
	return (res);
}

static int	is_valid_fractional_part(char *str, int *i, int *flag)
{
	if (str[*i] == '.' && str[*i + 1])
	{
		if (*flag == TRUE)
		{
			return (FALSE);
		}
		(*flag) = (TRUE);
		(*i)++;
	}
	return (TRUE);
}

int	ft_is_float(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = FALSE;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9' && flag == FALSE)
			i++;
		else if (!is_valid_fractional_part(str, &i, &flag))
			return (FALSE);
		else if (str[i] >= '0' && str[i] <= '9' && flag == TRUE)
			i++;
		else if ((str[i] == ' ' || str[i] == '\n'))
			i++;
		else
			return (FALSE);
	}
	return (TRUE);
}
