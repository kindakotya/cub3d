/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 00:47:04 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/30 17:57:12 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	add_sprite(t_args *s_args, t_sprite *sprite, t_sprite **sprites)
{
	sprite->size = s_args->win_h / sprite->dist;
	sprite->dir = atan2(sprite->y - s_args->player.y,
			sprite->x - s_args->player.x);
	while (sprite->dir - s_args->player.aov > M_PI)
		sprite->dir -= 6.28318530718;
	while (sprite->dir - s_args->player.aov < -M_PI)
		sprite->dir += 6.28318530718;
	sprite->w = (sprite->dir - s_args->player.aov) / 1.0471975512
		* s_args->win_w + s_args->win_w / 2 - sprite->size / 2;
	sprite->h = s_args->win_h / 2 - sprite->size / 2;
	push_sprite(sprites, sprite);
}

static int	check_sprite(t_ray *ray, t_sprite *sprites, double *x, double *y)
{
	*y = floor(ray->y) + 0.5;
	*x = floor(ray->x) + 0.5;
	if (!sprites)
		return (1);
	while (sprites)
	{
		if (fabs((sprites)->y - *y) < 0.1
			&& fabs((sprites)->x - *x) < 0.1)
			return (0);
		sprites = sprites->next;
	}
	return (1);
}

int	find_sprite(t_ray *ray, t_args *s_args, t_sprite **sprites)
{
	t_sprite		*sprite;
	double			x;
	double			y;

	if (ray->c < 1)
		return (1);
	if (s_args->map[(int)ray->y][(int)ray->x] == '2'
		&& check_sprite(ray, *sprites, &x, &y))
	{
		sprite = create_sprite();
		if (sprite == NULL)
		{
			free_sprites(*sprites);
			return (0);
		}
		sprite->x = x;
		sprite->y = y;
		sprite->dist = sqrt(pow(s_args->player.x - sprite->x, 2)
				+ pow(s_args->player.y - sprite->y, 2));
		if (sprite->dist > 0.2)
			add_sprite(s_args, sprite, sprites);
		else
			free(sprite);
	}
	return (1);
}

static void	sprite_line(t_all *s_all, t_sprite *sprites, t_ray *ray, int i)
{
	unsigned int	color;
	int				j;

	j = 0;
	while (j < sprites->size)
	{
		if (sprites->w + j < s_all->s_args->win_w
			&& sprites->dist < ray->walls[sprites->w + j])
		{
			color = take_color(&s_all->s_args->sprite.img,
					j * s_all->s_args->sprite.w / sprites->size,
					i * s_all->s_args->sprite.h / sprites->size);
			put_pixel(&s_all->s_mlx->img, sprites->w + j,
				sprites->h + i, color);
		}
		++j;
	}
}

void	draw_sprites(t_all *s_all, t_sprite *sprites, t_ray *ray)
{
	int	i;

	if (sprites == NULL)
		return ;
	while (sprites)
	{
		i = 0;
		while (i < sprites->size)
		{
			if (sprites->h + i < s_all->s_args->win_h)
				sprite_line(s_all, sprites, ray, i);
			++i;
		}
		sprites = sprites->next;
	}
}
