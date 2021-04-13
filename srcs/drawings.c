/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 19:19:54 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/01 17:50:00 by gmayweat         ###   ########.fr       */
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

unsigned int	*line_colors(t_img *img, int x, int y, int size)
{
	unsigned int	*color;
	int				i;

	color = malloc(size * sizeof(int));
	if (color == NULL)
		return (NULL);
	i = 0;
	while (i < sqr.side)
	{
		color[i] = take_color(img, x, y);
		++i;
	}
	return (color);
}

 void			draw_line(t_args *s_args, t_sqr sqr, t_mlx *s_mlx, double x)
{
	int i;
	unsigned int *color;
	i = 0;

	if (x < 0)
		x += s_args->tex_no.w;
	color = line_colors(&s_args->tex_no.img, x, 
			i * s_args->tex_no.h / sqr.side, sqr.side + 1);
	if (color == NULL)
		ft_exit(0, s_args, s_mlx, 2);
	i = 0;
	while (i < sqr.side)
	{
		if (sqr.x < s_args->win_w && sqr.y + i < s_args->win_h)
			my_mlx_pixel_put(&s_mlx->img, sqr.x, sqr.y + i, color[i]);
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
