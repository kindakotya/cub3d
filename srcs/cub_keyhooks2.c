/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_keyhooks2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 16:57:55 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/13 22:46:26 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_arrow_left_pressed(t_loop *s_loop)
{
	s_loop->s_args->player.a -= 0.2;
	// double prev;
	// double new;

	// prev = s_loop->s_args->player.angles[s_loop->s_args->player.aov];
	// if (s_loop->s_args->player.aov == 0)
	// 	s_loop->s_args->player.aov = 7;
	// else
	// 	--s_loop->s_args->player.aov;
	// new = s_loop->s_args->player.angles[s_loop->s_args->player.aov];
	// if (fabs(prev - new) < 0.01)
	// {
	// 	if (prev < new)
	// 		prev += M_PI / 3 / 12;
	// 	else
	// 		prev -= M_PI / 3 / 12;
	// 	raycast(s_loop->s_args, s_loop->s_mlx, prev);
	// 	mlx_put_image_to_window(s_loop->s_mlx->mlx, s_loop->s_mlx->win, s_loop->s_mlx->img.img, 0, 0);
	// }
	// else
	// 	return (1);
	return (0);
}

void	key_arrow_rigth_pressed(t_args *s_args)
{
	s_args->player.a += 0.2;
	// if (s_args->player.aov == 7)
	// 	s_args->player.aov = 0;
	// else
	// 	++s_args->player.aov;
}