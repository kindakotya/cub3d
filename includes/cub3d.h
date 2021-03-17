/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 17:10:33 by gmayweat          #+#    #+#             */
/*   Updated: 2021/03/17 19:48:11 by gmayweat         ###   ########.fr       */
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
// #include <OpenGL/gl.h>
// #include <OpenGL/glu.h>
// #include <OpenGL/glext.h>
// #include <GLUT/glut.h>
#include "mlx.h"

#define KEY_W 13
#define KEY_A 0
#define KEY_S 1
#define KEY_D 2
#define KEY_ESC 53

typedef struct         s_args
{
	size_t			res_x;
	size_t			res_y;
	char		*path_no;
	char		*path_so;
	char		*path_ea;
	char		*path_we;
	char		*path_s;
	unsigned int	floor;
	unsigned int	ceil;
	char		*map;
}                     t_args;




typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

typedef struct	s_vars
{
	void *mlx;
	void *win;
	t_data *img;
}				t_vars;


int     ft_parcecub(t_args *s_args, char *arglist);
int		cub_init(char *input);
#endif