/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 19:45:54 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/02 19:05:40 by gmayweat         ###   ########.fr       */
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

void		map_element(t_args *s_args, int side, int x, int y)
{
	int i;
	int j;
	int win_x;
	int win_y;

	i = 0;
	win_x = x * side;//(s_args->win_w / s_args->map_w - 1);
	win_y = y * side;
	while (i < side)
	{
		j = 0;
		while (j < side)
		{
			if (win_x + i < ft_min(s_args->win_h, s_args->win_w) && 
			win_y + j < ft_min(s_args->win_h, s_args->win_w))
			{
				s_args->win[win_y + j][win_x + i] = s_args->map[y][x];
			}
			++j;
		}
		++i;
	}
}
void		fill_map(t_args *s_args)
{
	int x;
	int y;

	y = 0;
	while (s_args->map[y])
	{
		x = 0;
		while (s_args->map[y][x])
		{
			map_element(s_args, ft_min(s_args->win_h, s_args->win_w) / 
				ft_max(s_args->map_w, s_args->map_h) - 1, x, y);
			++x;
		}
		++y;
	}
}

unsigned int	take_color(t_img *img, int x, int y)
{
	char *dst;

	if (x >= 0 && y >= 0)
	{
		dst = img->addr + (y * img->size_line + x * (img->bits_per_pixel / 8));
		return(*(unsigned int *) dst);
	}
	return (0);
}

t_sqr 		fill_sqr(int x, int y, int side, int color)
{
	t_sqr s_sqr;
	s_sqr.x = x;
	s_sqr.y = y;
	s_sqr.side = side;
	s_sqr.color = color;
	return (s_sqr);
}

void        add_floor_ceil(t_img *img, t_args *s_args)
{
	int x;
	int y;

	y = 0;
	while (y < s_args->win_h)
	{
		x = 0;
		while (x < s_args->win_w)
		{	
			if (y < s_args->win_h / 2)
				my_mlx_pixel_put(img, x++, y, s_args->floor);
			else
				my_mlx_pixel_put(img, x++, y, s_args->ceil);
		}
		++y;
	}
}



void			raycast(t_args *s_args, t_mlx *s_mlx)
{
	double c;
	double diff;
	int i;
	double fov;
	double x;
	double y;
	t_sqr line;
	int side;

	add_floor_ceil(&s_mlx->img, s_args);
	mlx_put_image_to_window(s_mlx->mlx, s_mlx->win,s_mlx->img.img, 0, 0);
	side = ft_min(s_args->win_h, s_args->win_w) / ft_max(s_args->map_h, s_args->map_w) - 1;
	// int mapx;
	// int mapy;
	diff = M_PI / 3 / s_args->win_w;
	fov = s_args->player.angles[s_args->player.aov] - M_PI / 3 / 2;
	i = 0;
	while (i < s_args->win_w)
	{
		c = 0.01;
		while (c)
		{
			x = (s_args->player.x + 0.5) * /*(s_args->win_h / s_args->map_w - 1)*/ side + c * cos(fov);
			y = (s_args->player.y + 0.5) * /*(s_argss->win_h / s_args->map_w - 1)*/ side + c * sin(fov);
			// mapx = s_args->player.x + c * cos(fov);
			// mapy = s_args->player.y + c * cos(fov);
			if (x < 0 || y < 0 || y >= s_args->win_h || x >= s_args->win_w || s_args->win[(int)y][(int)x] == '1')
				break ;
			my_mlx_pixel_put(&s_mlx->map, x, y, 0x00FFFF00);
			c += 0.05;
		}
		line = fill_sqr(i, 
		s_args->win_h / 2 - s_args->win_h * 15 / (c * cos(fov - s_args->player.angles[s_args->player.aov])) / 2,
		s_args->win_h * 15 / (c * cos(fov - s_args->player.angles[s_args->player.aov])), 255);// s_args->win_h * 1 / (c * cos(fov - s_args->player.aov)));
		x = s_args->tex_no.w * (x / side - floor(x / side + 0.5));
		y = s_args->tex_no.w * (y / side - floor(y / side + 0.5));
		if (i == 320)
			i = 320;
		if (fabs(x) < fabs(y))
			draw_line(s_args, line, s_mlx, y);
		else
			draw_line(s_args, line, s_mlx, x);
		++i;
		fov += diff;
	}
	mlx_put_image_to_window(s_mlx->mlx, s_mlx->win, s_mlx->img.img, 0, 0);
}

void		ft_free(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		++i;
	while (i)
		free(arr[--i]);
	free(arr);
}

void		ft_exit(t_args *s_args, t_mlx *s_mlx)
{
	ft_free(s_args->map);
	ft_free(s_args->win);
	free(s_args->path_ea);
	free(s_args->path_no);
	free(s_args->path_s);
	free(s_args->path_so);
	free(s_args->path_we);
	mlx_destroy_image(s_mlx->mlx, s_mlx->img.img);
	mlx_destroy_window(s_mlx->mlx, s_mlx->win);
	exit(0);
}

int				ft_loop(t_loop *s_loop)
{
	// sleep(1);
	s_loop->s_args->player.aov += M_PI / 12;
	draw_minimap(s_loop->s_args, s_loop->s_mlx);
	return (0);
}




int				cub_init(char *input)
{
	t_loop s_loop;
	t_args s_args;
	t_mlx s_mlx;
	// t_img img;
	int i = 0;
	// int y = 0;

	sleep(2);
	ft_clearstruct(&s_args);
	ft_getparam(input, &s_args);
	// s_mlx.img = &img;

	s_mlx.mlx = mlx_init();
	s_mlx.win = mlx_new_window(s_mlx.mlx, s_args.win_w, s_args.win_h, "cub3d");
	s_mlx.img.img = mlx_new_image(s_mlx.mlx, s_args.win_w, s_args.win_h);
	s_mlx.img.addr = mlx_get_data_addr(s_mlx.img.img, &s_mlx.img.bits_per_pixel,
						&s_mlx.img.size_line, &s_mlx.img.endian);
	s_mlx.minimap.img = mlx_new_image(s_mlx.mlx, s_args.win_h / 5 , s_args.win_h / 5);
	s_mlx.minimap.addr = mlx_get_data_addr(s_mlx.minimap.img, 
	&s_mlx.minimap.bits_per_pixel, &s_mlx.minimap.size_line, &s_mlx.minimap.endian);
	// mlx_key_hook(s_mlx.win, key, &s_mlx);
	fill_map(&s_args);
	draw_minimap(&s_args, &s_mlx);
	s_loop.s_args = &s_args;
	s_loop.s_mlx = &s_mlx;

	s_args.tex_no.img.img = mlx_xpm_file_to_image(s_mlx.mlx, s_args.path_no, &s_args.tex_no.w, &s_args.tex_no.h);
	s_args.tex_no.img.addr = mlx_get_data_addr(s_args.tex_no.img.img, &s_args.tex_no.img.bits_per_pixel,
											&s_args.tex_no.img.size_line, &s_args.tex_no.img.endian);

	mlx_put_image_to_window(s_mlx.mlx, s_mlx.win, s_args.tex_no.img.img, 0, 0);

	s_mlx.winmap = mlx_new_window(s_mlx.mlx, s_args.win_w, s_args.win_h, "map");
	s_mlx.map.img = mlx_new_image(s_mlx.mlx, s_args.win_w, s_args.win_h);
	s_mlx.map.addr = mlx_get_data_addr(s_mlx.map.img, &s_mlx.map.bits_per_pixel,
						&s_mlx.map.size_line, &s_mlx.map.endian);
	map(&s_args, &s_mlx);
	raycast(&s_args, &s_mlx);

	//mlx_put_image_to_window(s_mlx.mlx, s_mlx.winmap, s_mlx.map.img, 0, 0);
	mlx_put_image_to_window(s_mlx.mlx, s_mlx.win, s_mlx.img.img, 0, 0);
	mlx_hook(s_mlx.win, 2, 1, key_pressed, &s_loop);
	//mlx_loop_hook(s_mlx.mlx, ft_loop, &s_loop);
		mlx_loop(s_mlx.mlx);
	++i;
	return (0);
}