/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 19:45:54 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/16 17:45:43 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			clear_mlx(t_mlx *s_mlx)
{
	s_mlx->mlx = NULL;
	s_mlx->win = NULL;
	s_mlx->img.img = NULL;
	s_mlx->minimap.img = NULL;
	s_mlx->m_size = 0;
}

static void		clear_sprite(t_sprite *sprite)
{
	sprite->h = 0;
	sprite->w = 0;
	sprite->path = NULL;
	sprite->img.img = NULL;
}

static void		clear_args(t_args *s_args)
{
	s_args->win_w = 0;
	s_args->win_h = 0;
	s_args->win = NULL;
	s_args->player.x = 0;
	s_args->player.y = 0;
	s_args->player.aov = 1;
	s_args->screenshot = NULL;
	clear_sprite(&s_args->tex_ea);
	clear_sprite(&s_args->tex_no);
	clear_sprite(&s_args->tex_so);
	clear_sprite(&s_args->tex_we);
	clear_sprite(&s_args->sprite);
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



t_sqr 		fill_sqr(int x, int y, int side, int color)
{
	t_sqr s_sqr;
	s_sqr.x = x;
	s_sqr.y = y;
	s_sqr.side = side;
	s_sqr.color = color;
	return (s_sqr);
}



void	add_floor_ceil(t_img *img, t_args *s_args)
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

void		fill_line(t_line *line, t_args *s_args, t_ray *ray, t_sprite *tex)
{
	line->y = s_args->win_h / 2 - s_args->win_h * 15 / (ray->c * cos(ray->fov - s_args->player.aov)) / 2;
	line->length = s_args->win_h * 15 / (ray->c * cos(ray->fov - s_args->player.aov));
	line->tex = tex;
}



void			raycast(t_args *s_args, t_mlx *s_mlx)
{
	t_ray ray;
	double tex_x;
	double tex_y;
	t_line line;

	add_floor_ceil(&s_mlx->img, s_args);
	ray.fov = s_args->player.aov - 0.52359877559;
	line.x = 0;
	while (line.x < s_args->win_w)
	{
		ray.c = 0.01;
		while (ray.c)
		{
			ray.x = (s_args->player.x + 0.5) * s_args->side + ray.c * cos(ray.fov);
			ray.y = (s_args->player.y + 0.5) * s_args->side + ray.c * sin(ray.fov);
			if (ray.x < 0 || ray.y < 0 || ray.y >= s_args->win_h || ray.x >= s_args->win_w ||
			s_args->map[(int)ray.y / s_args->side][(int)ray.x / s_args->side] == '1')
				break ;
			my_mlx_pixel_put(&s_mlx->map, ray.x, ray.y, 0x00FFFF00);
			ray.c += 0.05;
		}
		fill_line(&line, s_args, &ray, &s_args->tex_so);
		tex_x = line.tex->w * (ray.x / s_args->side - floor(ray.x / s_args->side + 0.5));
		tex_y = line.tex->w * (ray.y / s_args->side - floor(ray.y / s_args->side + 0.5));
		if (fabs(tex_x) < fabs(tex_y))
			draw_line(s_args, &line, s_mlx, tex_y);
		else
			draw_line(s_args, &line, s_mlx, tex_x);
		++line.x;
		ray.fov += s_args->rays_density;
	}
	mlx_put_image_to_window(s_mlx->mlx, s_mlx->win, s_mlx->img.img, 0, 0);
}

int				ft_loop(t_loop *s_loop)
{
	// sleep(1);
	s_loop->s_args->player.aov += M_PI / 12;
	draw_minimap(s_loop->s_args, s_loop->s_mlx);
	return (0);
}




int				cub_init(char **input, int save)
{
	t_loop s_loop;
	t_args s_args;
	t_mlx s_mlx;
	// t_img img;
	// int y = 0;

	clear_args(&s_args);
	getparam(input[1], &s_args);
	if (save)
		s_args.screenshot = input[3];
	s_mlx = start_mlx(&s_args);
	//clear_mlx(&s_mlx);
	//mlx_destroy_image(s_mlx.mlx, s_args.tex_no.img.img);

	// s_mlx.img = &img;

	// 
	// 
	// s_mlx.img.img = mlx_new_image(s_mlx.mlx, s_args.win_w, s_args.win_h);
	// s_mlx.img.addr = mlx_get_data_addr(s_mlx.img.img, &s_mlx.img.bits_per_pixel,
	// 					&s_mlx.img.size_line, &s_mlx.img.endian);
	// s_mlx.minimap.img = mlx_new_image(s_mlx.mlx, s_args.win_h / 5 , s_args.win_h / 5);
	// s_mlx.minimap.addr = mlx_get_data_addr(s_mlx.minimap.img, 
	// &s_mlx.minimap.bits_per_pixel, &s_mlx.minimap.size_line, &s_mlx.minimap.endian);
	//mlx_key_hook(s_mlx.win, key, &s_mlx);
	fill_map(&s_args);
	// draw_minimap(&s_args, &s_mlx);
	 s_loop.s_args = &s_args;
	 s_loop.s_mlx = &s_mlx;

	// s_args.tex_no.img.img = mlx_xpm_file_to_image(s_mlx.mlx, s_args.path_no, &s_args.tex_no.w, &s_args.tex_no.h);
	// s_args.tex_no.img.addr = mlx_get_data_addr(s_args.tex_no.img.img, &s_args.tex_no.img.bits_per_pixel,
	// 										&s_args.tex_no.img.size_line, &s_args.tex_no.img.endian);

	// mlx_put_image_to_window(s_mlx.mlx, s_mlx.win, s_args.tex_no.img.img, 0, 0);

	s_mlx.winmap = mlx_new_window(s_mlx.mlx, s_args.win_w, s_args.win_h, "map");
	s_mlx.map.img = mlx_new_image(s_mlx.mlx, s_args.win_w, s_args.win_h);
	s_mlx.map.addr = mlx_get_data_addr(s_mlx.map.img, &s_mlx.map.bits_per_pixel,
						&s_mlx.map.size_line, &s_mlx.map.endian);
	map(&s_args, &s_mlx);
	raycast(&s_args, &s_mlx);



	mlx_put_image_to_window(s_mlx.mlx, s_mlx.win, s_mlx.img.img, 0, 0);
	mlx_hook(s_mlx.win, 2, 1, key_pressed, &s_loop);
	mlx_loop(s_mlx.mlx);

	return (0);
}