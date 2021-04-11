/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 19:45:54 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/11 18:27:42 by gmayweat         ###   ########.fr       */
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
			if (x < 0 || y < 0 || y >= s_args->win_h || x >= s_args->win_w ||
			s_args->map[(int)y / side][(int)x / side] == '1')
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

int				ft_loop(t_loop *s_loop)
{
	// sleep(1);
	s_loop->s_args->player.aov += M_PI / 12;
	draw_minimap(s_loop->s_args, s_loop->s_mlx);
	return (0);
}

int		screen_params(t_mlx *s_mlx, t_args *s_args)
{
	int screen_size[2];
	int i;

	i = 0;
	mlx_get_screen_size(s_mlx->mlx, &screen_size[0], &screen_size[1]);
	if (s_args->win_w < s_args->map_w || s_args->win_w > screen_size[0])
		s_args->win_w = screen_size[0];
	if (s_args->win_h < s_args->map_h || s_args->win_h > screen_size[1])
		s_args->win_h = screen_size[1] - screen_size[1] / 10;
	if ((s_args->win = malloc((s_args->win_h + 1) *sizeof(char*))) == NULL)
		ft_exit(0, s_args, s_mlx, 2);
	s_args->win[s_args->win_h] = NULL;
	while (i < s_args->win_h)
		if ((s_args->win[i++] = 
		ft_calloc((s_args->win_w + 1), sizeof(char))) == NULL)
			ft_exit(0, s_args, s_mlx, 2);
	if (s_args->win_h < s_args->win_w)
		return (s_args->win_h / 5);
	else
		return(s_args->win_w / 5);
}

int		load_texture(void *mlx, t_sprite *tex)
{
	if ((tex->img.img = 
		mlx_xpm_file_to_image(mlx, tex->path, &tex->w, &tex->h)) == NULL)
		return (0);
	if ((tex->img.addr = mlx_get_data_addr(tex->img.img,
	&tex->img.bits_per_pixel, &tex->img.size_line, &tex->img.endian)) == NULL)
		return (0);
	return (1);
	
}

void		load_textures(t_mlx *s_mlx, t_args *s_args)
{
	if ((load_texture(s_mlx->mlx, &s_args->tex_no)) == 0)
	{
		perror("Can't load north texture.\n");
		ft_exit(0, s_args, s_mlx, 16);
	}
	if ((load_texture(s_mlx->mlx, &s_args->tex_so)) == 0)
	{
		perror("Can't load south texture.\n");
		ft_exit(0, s_args, s_mlx, 16);
	}
	if ((load_texture(s_mlx->mlx, &s_args->tex_ea)) == 0)
	{
		perror("Can't load east texture.\n");
		ft_exit(0, s_args, s_mlx, 16);
	}
	if ((load_texture(s_mlx->mlx, &s_args->tex_we)) == 0)
	{
		perror("Can't load west texture.\n");
		ft_exit(0, s_args, s_mlx, 16);
	}
	if ((load_texture(s_mlx->mlx, &s_args->sprite)) == 0)
	{
		perror("Can't load sprite.\n");
		ft_exit(0, s_args, s_mlx, 16);
	}
}

void		create_images(t_args *s_args, t_mlx *s_mlx)
{
	if ((s_mlx->img.img = 
	mlx_new_image(s_mlx->mlx, s_args->win_w, s_args->win_h)) == NULL)
		ft_exit(0, s_args, s_mlx, 12);
	if ((s_mlx->img.addr = mlx_get_data_addr(s_mlx->img.img,
	&s_mlx->img.bits_per_pixel,
	&s_mlx->img.size_line, &s_mlx->img.endian)) == NULL)
		ft_exit(0, s_args, s_mlx, 13);
	if ((s_mlx->minimap.img = 
		mlx_new_image(s_mlx->mlx, s_mlx->m_size, s_mlx->m_size)) == NULL)
		ft_exit(0, s_args, s_mlx, 12);
	if ((s_mlx->minimap.addr = mlx_get_data_addr(s_mlx->minimap.img,
	&s_mlx->minimap.bits_per_pixel,
	&s_mlx->minimap.size_line, &s_mlx->minimap.endian)) == NULL)
		ft_exit(0, s_args, s_mlx, 13);
}

t_mlx	start_mlx(t_args *s_args)
{
	t_mlx s_mlx;

	if ((s_mlx.mlx = mlx_init()) == NULL)
		ft_exit(0, s_args, 0, 11);
	s_mlx.m_size = screen_params(s_mlx.mlx, s_args);
	if ((s_mlx.win =
	mlx_new_window(s_mlx.mlx, s_args->win_w, s_args->win_h, "cub3d")) == NULL)
		ft_exit(0, s_args, &s_mlx, 12);
	create_images(s_args, &s_mlx);
	load_textures(&s_mlx, s_args);
	return (s_mlx);
}


int				cub_init(char *input)
{
	t_loop s_loop;
	t_args s_args;
	t_mlx s_mlx;
	// t_img img;
	// int y = 0;

	clear_args(&s_args);
	getparam(input, &s_args);
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