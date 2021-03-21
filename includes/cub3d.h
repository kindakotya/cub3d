/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 17:10:33 by gmayweat          #+#    #+#             */
/*   Updated: 2021/03/22 01:17:54 by gmayweat         ###   ########.fr       */
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

typedef struct		s_args
{
	int			win_w;
	int			win_h;
	char			*path_no;
	char			*path_so;
	char			*path_ea;
	char			*path_we;
	char			*path_s;
	unsigned int	floor;
	unsigned int	ceil;
	char			**map;
	int				map_w;
	int				map_h;
	char			**win;
}					t_args;

typedef struct  s_img {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         size_line;
    int         endian;
}               t_img;

typedef struct	s_mlx
{
	void *mlx;
	void *win;
	t_img *img;
}				t_mlx;

typedef struct s_player
{
	float x;
	float y;
	float look_dir;
}				t_player;

int     ft_parcecub(t_args *s_args, char *arglist);
int		cub_init(char *input);
int		ft_getparam(char *input, t_args *s_args);
void			raycast(t_args *s_args, int x, int y, t_mlx *s_mlx);
#endif