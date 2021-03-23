/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 17:10:33 by gmayweat          #+#    #+#             */
/*   Updated: 2021/03/23 17:34:05 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>

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
#define KEY_ARROW_LEFT 123
#define KEY_ARROW_RIGTH 124
#define KEY_ESC 53
#define AOV_N M_PI / 2. * 3.
#define AOV_S M_PI / 2.
#define AOV_W M_PI
#define AOV_E M_PI * 2.

typedef struct s_rect
{
	int x;
	int y;
	int w;
	int h;
	unsigned int color;
}				t_rect;

typedef struct s_player
{
	int x;
	int y;
	int win_x;
	int win_y;
	float aov;
	float fov;
}				t_player;

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
	t_player		player;
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

typedef struct s_loop
{
	t_mlx *s_mlx;
	t_args *s_args;
}				t_loop;

int     ft_parcecub(t_args *s_args, char *arglist);
int		cub_init(char *input);
int		ft_getparam(char *input, t_args *s_args);
void			raycast(t_args *s_args,t_rect s_rect, t_mlx *s_mlx);
t_player			ft_find_player(t_args *s_args);
#endif