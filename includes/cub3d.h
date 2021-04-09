/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 17:10:33 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/09 03:52:32 by gmayweat         ###   ########.fr       */
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
#include "get_next_line.h"

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

typedef struct		s_sqr
{
	int				x;
	int				y;
	int				side;
	unsigned int	color;
}					t_sqr;

typedef struct		s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}					t_img;

typedef struct		s_player
{
	int			x;
	int			y;
	int			aov;
	double		angles[8];
}					t_player;

typedef struct		s_sprite
{
	t_img	img;
	int		w;
	int		h;
	char	*path;
}					t_sprite;

typedef struct		s_args
{
	int				win_w;
	int				win_h;
	unsigned int	floor;
	unsigned int	ceil;
	char			**map;
	int				map_w;
	int				map_h;
	char			**win;
	t_player		player;
	t_sprite		tex_no;
	t_sprite		tex_so;
	t_sprite		tex_ea;
	t_sprite		tex_we;
	t_sprite		sprite;
}					t_args;

typedef struct		s_mlx
{
	void		*mlx;
	void		*win;
	void		*winmap;
	t_img		img;
	t_img		map;
	t_img		minimap;
}					t_mlx;

typedef struct		s_loop
{
	t_mlx		*s_mlx;
	t_args		*s_args;
}					t_loop;

typedef struct		s_line
{
	int x;
	int y;
	int length;
	int *color;
	t_sprite tex;
}					t_line;

//int     parcecub(t_args *s_args, char *line);
int			cub_init(char *input);

void		raycast(t_args *s_args, t_mlx *s_mlx);



t_sqr 		fill_sqr(int x, int y, int side, int color);
unsigned int	take_color(t_img *img, int x, int y);
// drawing
void		draw_sqr(t_args *s_args, t_sqr s_sqr, t_img *img);
void		my_mlx_pixel_put(t_img *img, int x, int y, int color);
int			draw_minimap(t_args *s_args, t_mlx *s_mlx);
 void		draw_line(t_args *s_args, t_sqr sqr, t_mlx *s_mlx, double x);
// keyhooks
int			key_pressed(int keycode, t_loop *s_hook);
int			move_north(t_args *s_args);
int			move_south(t_args *s_args);
int			move_east(t_args *s_args);
int			move_west(t_args *s_args);
void		key_arrow_left_pressed(t_args *s_args);
void		key_arrow_rigth_pressed(t_args *s_args);
// parcer
void		skip_spaces(char **s);
void		skip_numbers(char **s);
char		**add_string(char **arr1, char *str);
int		is_side_of_world(int c);

int			get_res(char *line, t_args *s_args);
int			get_path(char **path, char *line);
int			get_color(char *line, unsigned int *color);
void		parce_map(t_args *s_args, int fd);
t_player	ft_find_player(t_args *s_args);
int			getparam(char *input, t_args *s_args);
void		get_map_res(t_args *s_args, int fd);

void		ft_exit(int fd, t_args *s_args, t_mlx *s_mlx, int return_val);

void map(t_args *s_args, t_mlx *s_mlx);
#endif