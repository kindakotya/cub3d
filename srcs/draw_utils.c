/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 00:46:38 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/30 01:53:01 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x > 0 && y > 0)
	{
		dst = img->addr + (y * img->size_line + x * (img->bits_per_pixel / 8));
		*(unsigned int *) dst = color;
	}
}

unsigned int	take_color(t_img *img, int x, int y)
{
	char	*dst;

	if (x >= 0 && y >= 0)
	{
		dst = img->addr + (y * img->size_line + x * (img->bits_per_pixel / 8));
		return (*(unsigned int *) dst);
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
