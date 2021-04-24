/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 19:19:06 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/23 01:49:05 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		set_img_black(t_img *img, int w, int h)
{
	int i;
	int j;

	i = 0;
	while(i < h)
	{
		j = 0;
		while (j < w)
		{
			put_pixel(img, j, i, 0);
			++j;
		}
		++i;
	}
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
				put_pixel(&s_mlx->map, x, y, 0x0000FF00);
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

int				draw_minimap(t_args *s_args, t_mlx *s_mlx)
{
	int		x;
	int		y;
	t_sqr	s_sqr;

	s_sqr.side = s_args->win_h / 100;
	set_img_black(&s_mlx->minimap, s_mlx->m_size, s_mlx->m_size);
	y = 0;
	while (s_args->map[y])
	{
		x = 0;
		while (s_args->map[y][x])
		{
			if (s_args->map[y][x] == '1' && fabs(s_args->player.x - x) < 10 && 
			fabs(s_args->player.y - y) < 10)
				draw_sqr(s_args, fill_sqr(
				(x - s_args->player.x + 10) * s_sqr.side, 
				(y - s_args->player.y + 10) * s_sqr.side , s_sqr.side, 
				0x00FF00FF), &s_mlx->minimap);
			++x;
		}
		++y;
	}
	draw_sqr(s_args, fill_sqr(s_args->win_h / 10 - s_sqr.side * 1.5, 
	s_args->win_h / 10 - s_sqr.side * 1.5, s_sqr.side / 2, 0x00FFFFFF), &s_mlx->minimap);
	mlx_put_image_to_window(s_mlx->mlx, s_mlx->win, s_mlx->minimap.img, 
	s_args->win_w - s_mlx->m_size, s_mlx->m_size * 4);
	return (1);
}