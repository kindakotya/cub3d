/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 19:45:54 by gmayweat          #+#    #+#             */
/*   Updated: 2021/03/22 01:17:21 by gmayweat         ###   ########.fr       */
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

void		put_block(t_args *s_args, int x, int y, t_mlx *s_mlx, int color)
{
	int i;
	int j;
	int block_x;
	int block_y;

	block_x = s_args->win_w / s_args->map_w - 1;// - s_args->win_w % maxx(s_args);
	block_y = s_args->win_h / s_args->map_h - 1;// - s_args->win_h % maxy(s_args);
	x *= block_x;
	y *= block_y;
	i = 0;
	while (i < block_x)
	{
		j = 0;
		while (j < block_y)
		{
			if (x + i < s_args->win_w && y + j < s_args->win_h)
			{
				my_mlx_pixel_put(s_mlx->img, x + i, y + j, color);
			}
			++j;
		}
		++i;
	}
}

 static int print_2dmap(t_args *s_args, t_mlx *s_mlx)
{
	int x;
	int y;


	y = 0;
	while (s_args->map[y])
    {
		x = 0;
		while (s_args->map[y][x])
		{
			if (s_args->map[y][x] == '1')
				put_block(s_args, x, y, s_mlx, s_args->floor);
			else if (s_args->map[y][x] == 'N')
				raycast(s_args, x, y, s_mlx);
			++x;
		}
		++y;
    }
	mlx_put_image_to_window(s_mlx->mlx, s_mlx->win, s_mlx->img->img, 0, 0);
	mlx_loop(s_mlx->mlx);
	return (1);
}

void			raycast(t_args *s_args, int x, int y, t_mlx *s_mlx)
{
	t_player player;
	float c;

	c = 1;
	player.look_dir = M_PI / 2;
	player.x = x;
	player.y = y;
	while (c)
	{
		x = player.x + c * cos(player.look_dir);
		y = player.y + c * sin(player.look_dir);
		if (s_args->map[y][x] != '0')
			break ;
		my_mlx_pixel_put(s_mlx->img->img, x, y, s_args->ceil);
		c += 0.1;
	}
}

int             cub_init(char *input)
{
	t_args s_args;
	t_mlx s_mlx;
	t_img img;
	// int x = 0;
	// int y = 0;

	ft_clearstruct(&s_args);
	ft_getparam(input, &s_args);
	s_mlx.img = &img;
	s_mlx.mlx = mlx_init();
	s_mlx.win = mlx_new_window(s_mlx.mlx, s_args.win_w, s_args.win_h, "cub3d");
	s_mlx.img->img = mlx_new_image(s_mlx.mlx, s_args.win_w, s_args.win_h);
	s_mlx.img->addr = mlx_get_data_addr(s_mlx.img->img, &s_mlx.img->bits_per_pixel,
						&s_mlx.img->size_line, &s_mlx.img->endian);
	print_2dmap(&s_args, &s_mlx);
	return (0);
}