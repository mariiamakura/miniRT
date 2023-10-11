/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:53:53 by mparasku          #+#    #+#             */
/*   Updated: 2023/10/06 17:12:09 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

int	main(int ac, char **av)
{
	t_rt	*rt;

	rt = NULL;
	if (ac != 2)
	{
		ft_putstr_fd("\033[31mError\n2 args required\n\033[0m", 2);
		ft_putstr_fd("\033[31m ./miniRT [scs]\n\033[0m", 2);
		return (-1);
	}
	if (!ft_parse(av[1], &rt))
	{
		ft_free_rt(rt);
		return (-1);
	}
	if (!ft_imag_init(&rt))
	{
		ft_free_rt(rt);
		return (-1);
	}
	mlx_terminate(rt->window->mlx);
	ft_free_rt(rt);
	return (0);
}
