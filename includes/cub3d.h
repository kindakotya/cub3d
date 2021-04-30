/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 17:10:33 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/30 17:35:20 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include "libft.h"
# include "mlx.h"
# include "get_next_line.h"

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_Q 12
# define KEY_E 14
# define KEY_F12 111
# define KEY_ARROW_LEFT 123
# define KEY_ARROW_RIGTH 124
# define KEY_ESC 53

typedef struct s_sqr
{
	int				x;
	int				y;
	int				side;
	unsigned int	color;
}				t_sqr;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}				t_img;

typedef struct s_player
{
	double			x;
	double			y;
	double			aov;
}					t_player;

typedef struct s_tex
{
	t_img	img;
	int		w;
	int		h;
	char	*path;
}				t_tex;

typedef struct s_args
{
	int				win_w;
	int				win_h;
	unsigned int	floor;
	unsigned int	ceil;
	char			**map;
	int				map_w;
	int				map_h;
	char			*screenshot;
	double			rays_density;
	t_player		player;
	t_tex			tex_no;
	t_tex			tex_so;
	t_tex			tex_ea;
	t_tex			tex_we;
	t_tex			sprite;
}				t_args;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	img;
	t_img	minimap;
	int		m_size;
}				t_mlx;

typedef struct s_ray
{
	double		x;
	double		y;
	double		prev_x[2];
	double		prev_y[2];
	double		c;
	double		fov;
	double		*walls;
	t_player	player;
}				t_ray;

typedef struct s_all
{
	t_mlx		*s_mlx;
	t_args		*s_args;
}				t_all;

typedef struct s_sprite
{
	double				dist;
	double				x;
	double				y;
	int					size;
	int					h;
	int					w;
	double				dir;
	struct s_sprite		*next;
}				t_sprite;

typedef struct s_line
{
	int			x;
	int			y;
	int			length;
	t_tex		*tex;
	double		tex_x;
	double		tex_y;
}				t_line;

void			cub_init(char **input, int save);
t_mlx			start_mlx(t_args *s_args);
void			raycast(t_all *s_all);
void			screenshot(t_args *s_args, t_mlx *s_mlx);
void			ft_exit(int fd, t_args *s_args, t_mlx *s_mlx, int return_val);
int				display_error(int err_no);
// struct clear
void			clear_mlx(t_mlx *s_mlx);
void			clear_args(t_args *s_args);
// drawing utils
void			draw_line(t_args *s_args, t_line *line, t_mlx *s_mlx, double x);
unsigned int	*line_colors(t_img *img, int x, int tex_size, int line_size);
unsigned int	take_color(t_img *img, int x, int y);
void			put_pixel(t_img *img, int x, int y, int color);
// drawing
void			drawing_params(t_args *s_args, t_mlx *s_mlx,
					t_ray *ray, t_line *line);
void			draw_floor_ceil(t_img *img, t_args *s_args);
int				minimap(t_args *s_args, t_mlx *s_mlx);
// keyhooks
int				key_pressed(int keycode, t_all *s_all);
// parcer utils
int				is_valid_char(int c);
void			skip_spaces(char **s);
void			skip_numbers(char **s);
char			**add_string(char **arr1, char *str);
int				is_side_of_world(int c);
// parcer
int				get_res(char *line, t_args *s_args);
int				get_path(char **path, char *line);
int				get_color(char *line, unsigned int *color);
void			parce_map(t_args *s_args, int fd, char **line);
t_player		find_player(t_args *s_args);
int				getparam(char *input, t_args *s_args);
void			get_map_res(t_args *s_args, int fd);
//sprites
void			push_sprite(t_sprite **sprites, t_sprite *sprite);
void			free_sprites(t_sprite *sprites);
t_sprite		*create_sprite(void);
int				find_sprite(t_ray *ray, t_args *s_args, t_sprite **sprites);
void			draw_sprites(t_all *s_all, t_sprite *sprites, t_ray *ray);
#endif