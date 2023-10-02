/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:53:53 by mparasku          #+#    #+#             */
/*   Updated: 2023/09/25 15:01:58 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

int	main(int ac, char **av)
{
	t_rt *rt;

	rt = NULL;
	if (ac != 2)
	{
		ft_putstr_fd("\033[31mError\n2 args required\n\033[0m", 2);
		ft_putstr_fd("\033[31m ./miniRT [scenes]\n\033[0m", 2);
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
	//ft_print_all(rt);
	ft_free_rt(rt);
	return (0);
}



//int main()
//{
//    t_matrix_3x3 matrix;
//    t_matrix_3x3 matrix_rev;
//    t_xyz vec_orig = {0.0, 0.0, 1.0};
//    t_xyz vec_fin = {0.5, 0.5, 0.5};
//    vec_fin = ft_normalize(&vec_fin);
//
//    matrix = ft_rotate(&vec_orig, &vec_fin);
//    t_xyz res = ft_matrix_xyz_multi(&matrix, &vec_orig);
//
//    matrix_rev = ft_rotate(&vec_fin, &vec_orig);
//    t_xyz res_rev = ft_matrix_xyz_multi(&matrix_rev, &vec_fin);
//
//    ft_print_xyz(&vec_orig);
//    ft_print_xyz(&vec_fin);
//    printf("\n");
//    ft_print_matrix(&matrix);
//    ft_print_xyz(&res);
//    printf("\n");
//    ft_print_matrix(&matrix_rev);
//    ft_print_xyz(&res_rev);
//
//}
//
