/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 17:10:33 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/28 02:24:29 by gmayweat         ###   ########.fr       */
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
#define KEY_Q 12
#define KEY_E 14
#define KEY_F12 111
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
	double			x;
	double			y;
	double			aov;
}					t_player;

typedef struct		s_tex
{
	t_img	img;
	int		w;
	int		h;
	char	*path;
}					t_tex;

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
	char			*screenshot;
	int				side;
	double			rays_density;
	t_player		player;
	t_tex		tex_no;
	t_tex		tex_so;
	t_tex		tex_ea;
	t_tex		tex_we;
	t_tex		sprite;
}					t_args;

typedef struct		s_mlx
{
	void		*mlx;
	void		*win;
	void		*winmap;
	t_img		img;
	t_img		map;
	t_img		minimap;
	int			m_size;
}					t_mlx;




typedef struct		s_ray
{
	double x;
	double y;
	double prev_x;
	double prev_y;
	double c;
	double fov;
	double *walls;
	double map_x;
	double map_y;
	t_player player;
}					t_ray;

typedef struct		s_all
{
	t_mlx		*s_mlx;
	t_args		*s_args;
}					t_all;


typedef struct		s_sprite
{
	double dist;
	double		x;
	double		y;
	int			size;
	double tex_x;
	double tex_y;
	int			win_x;
	int			h;
	int			w;
	double		dir;
	struct s_sprite *next;
}					t_sprite;

typedef struct		s_line
{
	int x;
	int y;
	int length;
	t_tex *tex;
	double tex_x;
	double tex_y;
	int is_sprite;
	t_sprite sprite;
}					t_line;



//int     parcecub(t_args *s_args, char *line);
int			cub_init(char **input, int save);

void		raycast(t_args *s_args, t_mlx *s_mlx);


int		display_error(int err_no);
t_sqr 		fill_sqr(int x, int y, int side, int color);
unsigned int	take_color(t_img *img, int x, int y);
// drawing
void		draw_sqr(t_args *s_args, t_sqr s_sqr, t_img *img);
void		put_pixel(t_img *img, int x, int y, int color);
int			draw_minimap(t_args *s_args, t_mlx *s_mlx);
void			draw_line(t_args *s_args, t_line *line, t_mlx *s_mlx, double x);
unsigned int	*line_colors(t_img *img, int x, int tex_size, int line_size);
unsigned int	take_color(t_img *img, int x, int y);
// keyhooks
int			key_pressed(int keycode, t_all *s_hook);
// parcer
int		is_valid_char(int c);
void		skip_spaces(char **s);
void		skip_numbers(char **s);
char		**add_string(char **arr1, char *str);
int		is_side_of_world(int c);

int			get_res(char *line, t_args *s_args);
int			get_path(char **path, char *line);
int			get_color(char *line, unsigned int *color);
void		parce_map(t_args *s_args, int fd, char **line);
t_player	find_player(t_args *s_args);
int			getparam(char *input, t_args *s_args);
void		get_map_res(t_args *s_args, int fd);

void		ft_exit(int fd, t_args *s_args, t_mlx *s_mlx, int return_val);
void		screenshot(t_args *s_args, t_mlx *s_mlx);
t_mlx	start_mlx(t_args *s_args);

void map(t_args *s_args, t_mlx *s_mlx);
#endif