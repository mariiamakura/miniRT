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

//
//void test(t_xyz vec_orig, t_xyz vec_fin) {
////    vec_orig = ft_normalize(&vec_orig);
////    vec_fin = ft_normalize(&vec_fin);
//    printf("org ");
//    ft_print_xyz(&vec_orig);
//    printf("fin ");
//    ft_print_xyz(&vec_fin);
////    printf("\n");
//
//    t_matrix_3x3 matrix = ft_rotate(&vec_orig, &vec_fin);
////    t_xyz res = ft_mul_xyz_mat(&vec_orig, &matrix);
//    t_xyz res = ft_mul_mat_xyz(&matrix, &vec_orig);
//    printf("res ");
//    ft_print_xyz(&res);
////    printf("\n");
//
////    t_matrix_3x3 matrix_rev = ft_rotate(&vec_fin, &vec_orig);
//////    t_xyz res_rev = ft_mul_xyz_mat(&vec_fin, &matrix_rev);
////    t_xyz res_rev = ft_mul_mat_xyz(&matrix_rev, &vec_fin);
////    printf("rev ");
////    ft_print_xyz(&res_rev);
////    printf("\n");
//}
//
//int main() {
////    printf("test1_1\n"); test((t_xyz){0.0, 0.0, 1.0}, (t_xyz){0.0, 0.0, -1.0});
////    printf("test1_2\n"); test((t_xyz){0.0, 0.0, 1.0}, (t_xyz){0.0, 0.0, 1.0});
////    printf("test1_3\n"); test((t_xyz){0.0, 0.0, 1.0}, (t_xyz){0.0, -1.0, 0.0});
////    printf("test1_4\n"); test((t_xyz){0.0, 0.0, 1.0}, (t_xyz){0.0, 1.0, 0.0});
////    printf("test1_5\n"); test((t_xyz){0.0, 0.0, 1.0}, (t_xyz){1.0, 0.0, 0.0});
////    printf("test1_6\n"); test((t_xyz){0.0, 0.0, 1.0}, (t_xyz){-1.0, 0.0, 0.0});
////
////    printf("test2_1\n"); test((t_xyz){0.0, 1.0, 0.0}, (t_xyz){0.0, 0.0, -1.0});
////    printf("test2_2\n"); test((t_xyz){0.0, 1.0, 0.0}, (t_xyz){0.0, 0.0, 1.0});
////    printf("test2_3\n"); test((t_xyz){0.0, 1.0, 0.0}, (t_xyz){0.0, -1.0, 0.0});
////    printf("test2_4\n"); test((t_xyz){0.0, 1.0, 0.0}, (t_xyz){0.0, 1.0, 0.0});
////    printf("test2_5\n"); test((t_xyz){0.0, 1.0, 0.0}, (t_xyz){1.0, 0.0, 0.0});
////    printf("test2_6\n"); test((t_xyz){0.0, 1.0, 0.0}, (t_xyz){-1.0, 0.0, 0.0});
////
////    printf("test3_1\n"); test((t_xyz){1.0, 0.0, 0.0}, (t_xyz){0.0, 0.0, -1.0});
////    printf("test3_2\n"); test((t_xyz){1.0, 0.0, 0.0}, (t_xyz){0.0, 0.0, 1.0});
////    printf("test3_3\n"); test((t_xyz){1.0, 0.0, 0.0}, (t_xyz){0.0, -1.0, 0.0});
////    printf("test3_4\n"); test((t_xyz){1.0, 0.0, 0.0}, (t_xyz){0.0, 1.0, 0.0});
////    printf("test3_5\n"); test((t_xyz){1.0, 0.0, 0.0}, (t_xyz){1.0, 0.0, 0.0});
////    printf("test3_6\n"); test((t_xyz){1.0, 0.0, 0.0}, (t_xyz){-1.0, 0.0, 0.0});
////
////    printf("test4_1\n"); test((t_xyz){0.0, 0.0, 1.0}, (t_xyz){0.0, 0.0, 0.5});
////    printf("test4_2\n"); test((t_xyz){0.0, 0.0, 1.0}, (t_xyz){0.0, 0.5, 0.0});
////    printf("test4_3\n"); test((t_xyz){0.0, 0.0, 1.0}, (t_xyz){0.5, 0.0, 0.0});
////    printf("test4_4\n"); test((t_xyz){0.0, 0.0, 1.0}, (t_xyz){0.5, 0.5, 0.5});
////    printf("test4_5\n"); test((t_xyz){0.0, 0.0, 1.0}, (t_xyz){0.0, 0.5, 0.5});
//    printf("test4_5\n"); test((t_xyz){0.0, 0.0, 1.0}, (t_xyz){0.5, 0.5, 0.0});
//}

