/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:49:37 by mparasku          #+#    #+#             */
/*   Updated: 2023/10/11 13:26:10 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <float.h>
# include <unistd.h>
# include <pthread.h>
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/libft.h"
# include "structs.h"
# include "functions.h"

# define CW 1000
# define CH 1000
# define VW 1
# define VH 1
# define FALSE 0
# define TRUE 1
# define NUM_THREADS 8

#endif