/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 19:19:54 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/30 17:49:39 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor_ceil(t_img *img, t_args *s_args)
{
	int	x;
	int	y;

	y = 0;
	while (y < s_args->win_h)
	{
		x = 0;
		while (x < s_args->win_w)
		{	
			if (y < s_args->win_h / 2)
				put_pixel(img, x++, y, s_args->floor);
			else
				put_pixel(img, x++, y, s_args->ceil);
		}
		++y;
	}
}

void	fill_line(t_line *line, t_args *s_args, t_ray *ray, t_tex *tex)
{
	line->y = s_args->win_h / 2 - s_args->win_h
		/ (ray->c * cos(ray->fov - s_args->player.aov)) / 2;
	line->length = s_args->win_h
		/ (ray->c * cos(ray->fov - s_args->player.aov));
	line->tex = tex;
	line->tex_x = ray->x - floor(ray->x + 0.5);
	line->tex_y = ray->y - floor(ray->y + 0.5);
}

static int	prev_choose_set(t_ray *ray, t_line *line, int flag)
{
	if (flag)
	{
		ray->prev_x[0] = ray->prev_x[1];
		ray->prev_y[0] = ray->prev_y[1];
		ray->prev_x[1] = ray->x;
		ray->prev_y[1] = ray->y;
	}
	if (line->x > 2 && fabs(ray->walls[line->x - 3] - ray->c) > 1)
		return (1);
	else
		return (0);
}

void	drawing_params(t_args *s_args, t_mlx *s_mlx, t_ray *ray, t_line *line)
{
	int	prev;

	prev = prev_choose_set(ray, line, 0);
	if (fabs(ray->prev_x[prev] - ray->x) > fabs(ray->prev_y[prev] - ray->y))
	{
		if (s_args->player.y < ray->y)
			fill_line(line, s_args, ray, &s_args->tex_no);
		else
			fill_line(line, s_args, ray, &s_args->tex_so);
	}
	else
	{
		if (s_args->player.x < ray->x)
			fill_line(line, s_args, ray, &s_args->tex_we);
		else
			fill_line(line, s_args, ray, &s_args->tex_ea);
	}
	if (fabs(line->tex_x) < fabs(line->tex_y))
		draw_line(s_args, line, s_mlx, line->tex_y * line->tex->w);
	else
		draw_line(s_args, line, s_mlx, line->tex_x * line->tex->w);
	prev_choose_set(ray, line, 1);
}

void	draw_line(t_args *s_args, t_line *line, t_mlx *s_mlx, double x)
{
	int				i;
	unsigned int	*color;

	if (x < 0)
		x += line->tex->w;
	color = line_colors(&line->tex->img, x, line->tex->h, line->length);
	if (color == NULL)
		ft_exit(0, s_args, s_mlx, 2);
	i = 0;
	while (i < line->length)
	{
		if (line->x < s_args->win_w && line->y + i < s_args->win_h)
			put_pixel(&s_mlx->img, line->x, line->y + i, color[i]);
		++i;
	}
	free(color);
}
