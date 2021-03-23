/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 19:45:54 by gmayweat          #+#    #+#             */
/*   Updated: 2021/03/23 03:18:41 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void     ft_clearstruct(t_args *s_args)
{
	s_args->win_w = 0;
	s_args->win_h = 0;
	s_args->path_no = NULL;
	s_args->path_so = NULL;
	s_args->path_ea = NULL;
	s_args->path_we = NULL;
	s_args->path_s = NULL;
	s_args->floor = 0;
	s_args->ceil = 0;
	s_args->map = NULL;
	s_args->map_h = 0;
	s_args->map_w = 0;
}

void            my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char    *dst;

    dst = img->addr + (y * img->size_line + x * (img->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void		draw_rect(t_args *s_args, t_rect rect, t_mlx *s_mlx)
{
	int i;
	int j;
	// int block_w;
	// int block_h;

	// block_w = s_args->win_w / s_args->map_w - 1;// - s_args->win_w % maxx(s_args);
	// block_h = s_args->win_h / s_args->map_h - 1;// - s_args->win_h % maxy(s_args);
	i = 0;
	while (i < rect.w)
	{
		j = 0;
		while (j < rect.h)
		{
			if (rect.x + i < s_args->win_w && rect.y + j < s_args->win_h)
			{
				my_mlx_pixel_put(s_mlx->img, rect.x + i, rect.y + j, rect.color);
			}
			++j;
		}
		++i;
	}
}

void		fill_map(t_args *s_args, t_rect rect, int x, int y)
{
	int i;
	int j;
	// int block_w;
	// int block_h;

	// block_w = s_args->win_w / s_args->map_w - 1;// - s_args->win_w % maxx(s_args);
	// block_h = s_args->win_h / s_args->map_h - 1;// - s_args->win_h % maxy(s_args);
	i = 0;
	rect.x = x * rect.w;
	rect.y = y * rect.h;
	while (i < rect.w)
	{
		j = 0;
		while (j < rect.h)
		{
			if (rect.x + i < s_args->win_w && rect.y + j < s_args->win_h)
			{
				s_args->win[rect.y + j][rect.x + i] = s_args->map[y][x];
			}
			++j;
		}
		++i;
	}
}
t_rect 		fill_rect(int x, int y, int w, int h)
{
	t_rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	return (rect);
}

void        black_screen(t_args *s_args, t_mlx *s_mlx)
{
	int x;
	int y;

	y = 0;
	while (y < s_args->win_h)
	{
		x = 0;
		while (x < s_args->win_w)
		{
			my_mlx_pixel_put(s_mlx->img, x++, y, 0);
		}
		++y;
	}
}
 static int print_2dmap(t_args *s_args, t_mlx *s_mlx)
{
	int x;
	int y;
	t_rect rect;
	

	rect.h = s_args->win_h / s_args->map_h - 1;
	rect.w = s_args->win_w / s_args->map_w / 2 - 1;
	black_screen(s_args, s_mlx);
	y = 0;
	while (s_args->map[y])
    {
		x = 0;
		while (s_args->map[y][x])
		{
			fill_map(s_args, rect, x, y);
			if (s_args->map[y][x] == '1')
			{
				rect.x = x * rect.w;
				rect.y = y * rect.h;
				rect.color = s_args->floor;
				draw_rect(s_args, rect, s_mlx);
			}
			++x;
		}
		++y;
    }
	// rect = fill_rect(s_args->player.x * rect.w + rect.w / 2, s_args->player.y * rect.h + rect.h / 2, 5, 5);
	// rect.color = 0x000000FF;
	// draw_rect(s_args, rect, s_mlx);
	
	raycast(s_args, rect, s_mlx);
	mlx_put_image_to_window(s_mlx->mlx, s_mlx->win, s_mlx->img->img, 0, 0);
	return (1);
}

void			raycast(t_args *s_args, t_rect s_rect, t_mlx *s_mlx)
{
	float c;
	float diff;
	int i;
	float fov;
	int x;
	int y;
	// int mapx;
	// int mapy;
	diff = M_PI / 3 / 100;
	fov = s_args->player.aov - M_PI / 3 / 2;
	i = 0;
	while (i < 100)
	{
		c = 0.1;
		while (c)
		{
			x = (s_args->player.x + 0.5) * s_rect.w + c * cos(fov);
			y = (s_args->player.y + 0.5)  * s_rect.h + c * sin(fov);
			// mapx = s_args->player.x + c * cos(fov);
			// mapy = s_args->player.y + c * cos(fov);
			if (y >= s_args->win_h || x >= s_args->win_w || s_args->win[y][x] == '1'
			||	x < 0 || y < 0)
				break ;
			my_mlx_pixel_put(s_mlx->img, x, y, s_args->ceil);
			c += 0.05;
		}
		draw_rect(s_args, s_args->win_w / 2 + i, s_args->map_h / (1 - 1 / c) / 2, s_mlx, 1, s_args->win_h / (c * cos(fov - player.look_dir)), s_args->ceil);
		++i;
		fov += diff;
	}
}
int key()
{
	exit(0);
	return (1);
}

int				ft_loop(t_loop *s_loop)
{
	 sleep(1);
	s_loop->s_args->player.aov += M_PI / 12;
	print_2dmap(s_loop->s_args, s_loop->s_mlx);
	return (0);
}

int             cub_init(char *input)
{
	t_loop s_loop;
	t_args s_args;
	t_mlx s_mlx;
	t_img img;
	int i = 0;
	// int y = 0;

	ft_clearstruct(&s_args);
	ft_getparam(input, &s_args);
	s_mlx.img = &img;
	s_mlx.mlx = mlx_init();
	s_mlx.win = mlx_new_window(s_mlx.mlx, s_args.win_w, s_args.win_h, "cub3d");
	s_mlx.img->img = mlx_new_image(s_mlx.mlx, s_args.win_w, s_args.win_h);
	s_mlx.img->addr = mlx_get_data_addr(s_mlx.img->img, &s_mlx.img->bits_per_pixel,
						&s_mlx.img->size_line, &s_mlx.img->endian);
	// mlx_key_hook(s_mlx.win, key, &s_mlx);
	print_2dmap(&s_args, &s_mlx);
	s_loop.s_args = &s_args;
	s_loop.s_mlx = &s_mlx;
	s_args.player.aov += M_PI / 12;
	mlx_loop_hook(s_mlx.mlx, ft_loop, &s_loop);
		mlx_loop(s_mlx.mlx);
	++i;
	return (0);
}