/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 00:47:07 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/30 00:47:10 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_mlx(t_mlx *s_mlx)
{
	s_mlx->mlx = NULL;
	s_mlx->win = NULL;
	s_mlx->img.img = NULL;
	s_mlx->minimap.img = NULL;
	s_mlx->m_size = 0;
}

static void	clear_tex(t_tex *sprite)
{
	sprite->h = 0;
	sprite->w = 0;
	sprite->path = NULL;
	sprite->img.img = NULL;
}

void	clear_args(t_args *s_args)
{
	s_args->win_w = 0;
	s_args->win_h = 0;
	s_args->player.x = 0;
	s_args->player.y = 0;
	s_args->player.aov = 1;
	s_args->screenshot = NULL;
	clear_tex(&s_args->tex_ea);
	clear_tex(&s_args->tex_no);
	clear_tex(&s_args->tex_so);
	clear_tex(&s_args->tex_we);
	clear_tex(&s_args->sprite);
	s_args->floor = 0;
	s_args->ceil = 0;
	s_args->map = NULL;
	s_args->map_h = 0;
	s_args->map_w = 0;
}
