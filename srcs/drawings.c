/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 19:19:54 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/16 17:41:50 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;
	if (x > 0 && y > 0)
	{
		dst = img->addr + (y * img->size_line + x * (img->bits_per_pixel / 8));
		*(unsigned int *) dst = color;
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

unsigned int	*line_colors(t_img *img, int x, int tex_size, int line_size)
{
	unsigned int	*color;
	int				i;

	color = malloc(line_size * sizeof(int));
	if (color == NULL)
		return (NULL);
	i = 0;
	while (i < line_size)
	{
		color[i] = take_color(img, x, i * tex_size / line_size);
		++i;
	}
	return (color);
}

void			draw_line(t_args *s_args, t_line *line, t_mlx *s_mlx, double x)
{
	int i;
	unsigned int *color;

	if (x < 0)
		x += line->tex->w;
	color = line_colors(&line->tex->img, x, line->tex->h, line->length);
	if (color == NULL)
		ft_exit(0, s_args, s_mlx, 2);
	i = 0;
	while (i < line->length)
	{
		if (line->x < s_args->win_w && line->y + i < s_args->win_h)
			my_mlx_pixel_put(&s_mlx->img, line->x, line->y + i, color[i]);
		++i;
	}
	free(color);
}

void		draw_sqr(t_args *s_args, t_sqr s_sqr, t_img *img)
{
	int i;
	int j;

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
