/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 17:10:33 by gmayweat          #+#    #+#             */
/*   Updated: 2021/03/10 19:18:21 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUB3D_H
#define CUB3D_H

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "libft.h"
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>
#include "mlx.h"
#include "mlx_int.h"
#include "mlx_new_window.h"
#include "mlx_opengl.h"
#include "mlx_png.h"

typedef struct         s_struct
{
	size_t			res_x;
	size_t			res_y;
	const char		*path_no;
	const char		*path_so;
	const char		*path_ea;
	const char		*path_we;
	const char		*path_s;
	unsigned char	floor_r;
	unsigned char	floor_g;
	unsigned char	floor_b;
	unsigned char	ceil_r;
	unsigned char	ceil_g;
	unsigned char	ceil_b;
	const char		*map;
}                     t_args;
int     ft_parcecub(t_args *s_args, char *arglist);
#endif