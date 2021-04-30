/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 00:47:01 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/30 01:40:07 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	push_mid(t_sprite *sprites, t_sprite *sprite)
{
	t_sprite	*meow;

	meow = sprites;
	while (meow && sprite->dist <= meow->dist)
		meow = meow->next;
	while (sprites->next && sprites->next != meow)
		sprites = sprites->next;
	sprites->next = sprite;
	sprite->next = meow;
}

void	push_sprite(t_sprite **sprites, t_sprite *sprite)
{
	if (*sprites == NULL)
	{
		*sprites = sprite;
		return ;
	}
	if (sprite->dist > (*sprites)->dist)
	{
		sprite->next = *sprites;
		*sprites = sprite;
		return ;
	}
	push_mid(*sprites, sprite);
}

t_sprite	*create_sprite(void)
{
	t_sprite	*sprites;

	sprites = malloc(sizeof(t_sprite));
	if (sprites == NULL)
		return (NULL);
	sprites->next = NULL;
	return (sprites);
}

void	free_sprites(t_sprite *sprites)
{
	t_sprite	*prev_sprite;

	if (sprites)
	{
		while (sprites->next)
		{
			prev_sprite = sprites;
			sprites = sprites->next;
			free(prev_sprite);
		}
		free(sprites);
	}
}
