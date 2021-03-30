/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 19:45:54 by gmayweat          #+#    #+#             */
/*   Updated: 2021/03/31 01:48:04 by gmayweat         ###   ########.fr       */
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
    if (x > 0 && y > 0)
    {
	    dst = img->addr + (y * img->size_line + x * (img->bits_per_pixel / 8));
	    *(unsigned int *) dst = color;
    }
}

void		draw_sqr(t_args *s_args, t_sqr s_sqr, t_img *img)
{
	int i;
	int j;
	// int block_w;
	// int block_h;

	// block_w = s_args->win_w / s_args->map_w - 1;// - s_args->win_w % maxx(s_args);
	// block_h = s_args->win_h / s_args->map_h - 1;// - s_args->win_h % maxy(s_args);
	i = 0;
	while (i < s_sqr.side)
	{
		j = 0;
		while (j < s_sqr.side)
		{
			if (s_sqr.x + i < s_args->win_w && s_sqr.y + j < s_args->win_h)
			{
				my_mlx_pixel_put(img, s_sqr.x + i, s_sqr.y + j, s_sqr.color);
			}
			++j;
		}
		++i;
	}
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
			if (win_x + i < s_args->win_h && win_y + j < s_args->win_h)
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
			map_element(s_args, s_args->win_h / s_args->map_w - 1, x, y);
			++x;
		}
		++y;
	}
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

void        set_img_black(t_img *img, int w, int h)
{
	int i;
	int j;

	i = 0;
	while(i < h)
	{
		j = 0;
		while (j < w)
		{
			my_mlx_pixel_put(img, j, i, 0);
			++j;
		}
		++i;
	}
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
int draw_minimap(t_args *s_args, t_mlx *s_mlx)
{
	int x;
	int y;
	t_sqr s_sqr;

	s_sqr.side = s_args->win_h / 100;
	set_img_black(&s_mlx->minimap, s_args->win_h / 5, s_args->win_h / 5);
	y = 0;
	while (s_args->map[y])
    {
		x = 0;
		while (s_args->map[y][x])
		{
			if (s_args->map[y][x] == '1' && abs(s_args->player.x - x) < 10 && 
			abs(s_args->player.y - y) < 10)
				draw_sqr(s_args, fill_sqr(
				(x - s_args->player.x + 10) * s_sqr.side, 
				(y - s_args->player.y + 10) * s_sqr.side , s_sqr.side, 
				0x00FF00FF), &s_mlx->minimap);
			++x;
		}
		++y;
    }
	draw_sqr(s_args, fill_sqr(s_args->win_h / 10 - 5, 
	s_args->win_h / 10 - 5, 5, 1000), &s_mlx->minimap);
	mlx_put_image_to_window(s_mlx->mlx, s_mlx->win, s_mlx->minimap.img, 
	s_args->win_w - s_args->win_h / 5, s_args->win_h / 5 * 4);
	return (1);
}

 void			draw_line(t_args *s_args, t_sqr sqr, t_mlx *s_mlx)
{
	int i;

	i = 0;
	while (i < sqr.side)
	{
		if (sqr.x < s_args->win_w && sqr.y + i < s_args->win_h)
			my_mlx_pixel_put(&s_mlx->img, sqr.x, sqr.y + i, sqr.color);
		++i;
	}
}

void			raycast(t_args *s_args, t_mlx *s_mlx)
{
	float c;
	float diff;
	int i;
	float fov;
	int x;
	int y;
	t_sqr line;
	int side;

	add_floor_ceil(&s_mlx->img, s_args);
	side = s_args->win_h / s_args->map_h - 1;
	// int mapx;
	// int mapy;
	diff = M_PI / 3 / s_args->win_w;
	fov = s_args->player.aov - M_PI / 3 / 2;
	i = 0;
	while (i < s_args->win_w)
	{
		c = 0.1;
		while (c)
		{
			x = (s_args->player.x + 0.5) * (s_args->win_h / s_args->map_w - 1) + c * cos(fov);
			y = (s_args->player.y + 0.5) * (s_args->win_h / s_args->map_w - 1) + c * sin(fov);
			// mapx = s_args->player.x + c * cos(fov);
			// mapy = s_args->player.y + c * cos(fov);
			if (x < 0 || y < 0 || y >= s_args->win_h || x >= s_args->win_w || s_args->win[y][x] == '1')
				break ;
			my_mlx_pixel_put(&s_mlx->map, x, y, 0x00FFFF00);
			c += 0.05;
		}
		line = fill_sqr(i, 
		s_args->win_h / 2 - s_args->win_h * 15 / (c * cos(fov - s_args->player.aov)) / 2,
		s_args->win_h * 15 / (c * cos(fov - s_args->player.aov)), 255);// s_args->win_h * 1 / (c * cos(fov - s_args->player.aov)));
		draw_line(s_args, line, s_mlx);
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

void map(t_args *s_args, t_mlx *s_mlx)
{
		int x;
	int y;
//	t_sqr s_sqr;

	y = 0;
//	s_sqr.side = s_args->win_h / s_args->map_h - 1;
	set_img_black(&s_mlx->map, s_args->win_w, s_args->win_h);
	while (s_args->win[y])
    {
		x = 0;
		while (s_args->win[y][x])
		{
			if (s_args->win[y][x] == '1')
				my_mlx_pixel_put(&s_mlx->map, x, y, 0x0000FF00);
				// draw_sqr(s_args, fill_sqr(
				// (x) * s_sqr.side,
				// (y) * s_sqr.side , s_sqr.side,
				// 0x00FF00FF), &s_mlx->map);
			++x;
		}
		++y;
    }
	//draw_sqr(s_args, fill_sqr(x * (s_args->win_h / s_args->map_h - 1),
	//y * (s_args->win_h / s_args->map_h - 1), 5, 1000), &s_mlx->minimap);
	mlx_put_image_to_window(s_mlx->mlx, s_mlx->winmap, s_mlx->map.img, 0, 0);
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