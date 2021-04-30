/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 19:19:06 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/30 02:49:37 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_sqr	fill_sqr(int x, int y, int side, int color)
{
	t_sqr	sqr;

	sqr.x = x;
	sqr.y = y;
	sqr.side = side;
	sqr.color = color;
	return (sqr);
}

static void	set_img_black(t_img *img, int w, int h)
{
	int	i;
	int	j;

	i = 0;
	while (i < h)
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

static void	draw_sqr(t_args *s_args, t_sqr sqr, t_img *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < sqr.side)
	{
		j = 0;
		while (j < sqr.side)
		{
			if (sqr.x + i < s_args->win_w && sqr.y + j < s_args->win_h)
			{
				put_pixel(img, sqr.x + i, sqr.y + j, sqr.color);
			}
			++j;
		}
		++i;
	}
}

static void	draw_minimap(t_args *s_args, t_mlx *s_mlx, t_sqr *sqr)
{
	int	x;
	int	y;

	y = 0;
	while (s_args->map[y])
	{
		x = 0;
		while (s_args->map[y][x])
		{
			if (s_args->map[y][x] == '1' && fabs(s_args->player.x - x) < 10
				&& fabs(s_args->player.y - y) < 10)
				draw_sqr(s_args, fill_sqr(
						(x - s_args->player.x + 10) * sqr->side,
						(y - s_args->player.y + 10) * sqr->side, sqr->side,
						0x00FF00FF), &s_mlx->minimap);
			++x;
		}
		++y;
	}
}

int	minimap(t_args *s_args, t_mlx *s_mlx)
{
	t_sqr	sqr;

	sqr.side = s_mlx->m_size / 20;
	set_img_black(&s_mlx->minimap, s_mlx->m_size, s_mlx->m_size);
	draw_minimap(s_args, s_mlx, &sqr);
	draw_sqr(s_args, fill_sqr(s_mlx->m_size / 2 - sqr.side * 6 / 5,
			s_mlx->m_size / 2 - sqr.side * 6 / 5, sqr.side / 2,
			0x00FFFFFF), &s_mlx->minimap);
	mlx_put_image_to_window(s_mlx->mlx, s_mlx->win, s_mlx->minimap.img,
		s_args->win_w - s_mlx->m_size, s_mlx->m_size * 4);
	return (1);
}
