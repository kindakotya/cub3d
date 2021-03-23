/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 19:45:54 by gmayweat          #+#    #+#             */
/*   Updated: 2021/03/24 00:01:36 by gmayweat         ###   ########.fr       */
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
	i = 0;
	// while (s_args->win[i])
	// {
	// 	printf("%s\n", s_args->win[i++]);
	// }
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

//  void			draw_column(t_args *s_args, t_mlx *s_mlx)
// {

// }

void			raycast(t_args *s_args, t_rect s_rect, t_mlx *s_mlx)
{
	float c;
	float diff;
	int i;
	float fov;
	int x;
	int y;
	t_rect column;
	// int mapx;
	// int mapy;
	diff = M_PI / 3 / s_args->win_w * 2;
	fov = s_args->player.aov - M_PI / 3 / 2;
	i = 0;
	while (i < s_args->win_w / 2)
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
		column = fill_rect(s_args->win_w / 2 + i, s_args->win_h / 2 - s_args->win_h * 10 / (c * cos(fov - s_args->player.aov)) / 2, 1, s_args->win_h * 15 / (c * cos(fov - s_args->player.aov)));
		column.color = s_args->ceil;
		draw_rect(s_args, column, s_mlx);
		++i;
		fov += diff;
	}
}

void		key_a_pressed(t_args *s_args)
{
	// s_args->map[player.y][play]
	if (fabs(s_args->player.aov - AOV_N) < 0.001)
	{
		if (s_args->map[s_args->player.y][s_args->player.x - 1] == '0')
			--s_args->player.x;
	}
	else if (fabs(s_args->player.aov - AOV_S) < 0.001)
	{
		if (s_args->map[s_args->player.y][s_args->player.x + 1] == '0')
			++s_args->player.x;
	}
	else if (fabs(s_args->player.aov - AOV_W) < 0.001)
	{
		if (s_args->map[s_args->player.y + 1][s_args->player.x] == '0')
		++s_args->player.y;
	}
	else if (fabs(s_args->player.aov - AOV_E) < 0.001)
		if (s_args->map[s_args->player.y - 1][s_args->player.x] == '0')
			--s_args->player.y;
}

void		key_w_pressed(t_args *s_args)
{
	if (fabs(s_args->player.aov - AOV_N) < 0.001)
	{
		if (s_args->map[s_args->player.y - 1][s_args->player.x] == '0')
			--s_args->player.y;
	}
	else if (fabs(s_args->player.aov - AOV_S) < 0.001)
	{
		if (s_args->map[s_args->player.y + 1][s_args->player.x] == '0')
			++s_args->player.y;
	}
	else if (fabs(s_args->player.aov - AOV_W) < 0.001)
	{
		if (s_args->map[s_args->player.y][s_args->player.x - 1] == '0')
		--s_args->player.x;
	}
	else if (fabs(s_args->player.aov - AOV_E) < 0.001)
		if (s_args->map[s_args->player.y][s_args->player.x + 1] == '0')
			++s_args->player.x;
}

void		key_d_pressed(t_args *s_args)
{
	if (fabs(s_args->player.aov - AOV_N) < 0.001)
	{
		if (s_args->map[s_args->player.y][s_args->player.x + 1] == '0')
			++s_args->player.x;
	}
	else if (fabs(s_args->player.aov - AOV_S) < 0.001)
	{
		if (s_args->map[s_args->player.y][s_args->player.x - 1] == '0')
			--s_args->player.x;
	}
	else if (fabs(s_args->player.aov - AOV_W) < 0.001)
	{
		if (s_args->map[s_args->player.y - 1][s_args->player.x] == '0')
		--s_args->player.y;
	}
	else if (fabs(s_args->player.aov - AOV_E) < 0.001)
		if (s_args->map[s_args->player.y + 1][s_args->player.x] == '0')
			++s_args->player.y;
}

void		key_s_pressed(t_args *s_args)
{
	if (fabs(s_args->player.aov - AOV_N) < 0.001)
	{
		if (s_args->map[s_args->player.y + 1][s_args->player.x] == '0')
			++s_args->player.y;
	}
	else if (fabs(s_args->player.aov - AOV_S) < 0.001)
	{
		if (s_args->map[s_args->player.y - 1][s_args->player.x] == '0')
			--s_args->player.y;
	}
	else if (fabs(s_args->player.aov - AOV_W) < 0.001)
	{
		if (s_args->map[s_args->player.y][s_args->player.x + 1] == '0')
		++s_args->player.x;
	}
	else if (fabs(s_args->player.aov - AOV_E) < 0.001)
		if (s_args->map[s_args->player.y][s_args->player.x - 1] == '0')
			--s_args->player.x;
}

void	key_arrow_left_pressed(t_args *s_args)
{
	if (fabs(s_args->player.aov - AOV_N) < 0.001)
		s_args->player.aov = AOV_W;
	else if (fabs(s_args->player.aov - AOV_W) < 0.001)
		s_args->player.aov = AOV_S;
	else if (fabs(s_args->player.aov - AOV_S) < 0.001)
		s_args->player.aov = AOV_E;
	else if (fabs(s_args->player.aov - AOV_E) < 0.001)
		s_args->player.aov = AOV_N;
}

void	key_arrow_rigth_pressed(t_args *s_args)
{
	if (fabs(s_args->player.aov - AOV_N) < 0.001)
		s_args->player.aov = AOV_E;
	else if (fabs(s_args->player.aov - AOV_E) < 0.001)
		s_args->player.aov = AOV_S;
	else if (fabs(s_args->player.aov - AOV_S) < 0.001)
		s_args->player.aov = AOV_W;
	else if (fabs(s_args->player.aov - AOV_W) < 0.001)
		s_args->player.aov = AOV_N;
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
	mlx_destroy_image(s_mlx->mlx, s_mlx->img->img);
	mlx_destroy_window(s_mlx->mlx, s_mlx->win);
	exit(0);
}

int key_pressed(int keycode, t_loop *s_hook)
{
	if (keycode == KEY_A)
		key_a_pressed(s_hook->s_args);
	else if (keycode == KEY_D)
		key_d_pressed(s_hook->s_args);
	else if (keycode == KEY_W)
		key_w_pressed(s_hook->s_args);
	else if (keycode == KEY_S)
		key_s_pressed(s_hook->s_args);
	else if (keycode == KEY_ARROW_LEFT)
		key_arrow_left_pressed(s_hook->s_args);
	else if (keycode == KEY_ARROW_RIGTH)
		key_arrow_rigth_pressed(s_hook->s_args);
	else if (keycode == KEY_ESC)
		ft_exit(s_hook->s_args, s_hook->s_mlx);
	print_2dmap(s_hook->s_args, s_hook->s_mlx);
	return (1);
}

int				ft_loop(t_loop *s_loop)
{
	// sleep(1);
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

	sleep(2);
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
	mlx_hook(s_mlx.win, 2, 1, key_pressed, &s_loop);
	//mlx_loop_hook(s_mlx.mlx, ft_loop, &s_loop);
		mlx_loop(s_mlx.mlx);
	++i;
	return (0);
}