/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 17:19:27 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/13 23:16:07 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		move_north(t_args *s_args)
{
	if (s_args->map[(int)s_args->player.y - 1][(int)s_args->player.x] != '1')
		--s_args->player.y;
	return (1);
}

int		move_south(t_args *s_args)
{
	if (s_args->map[(int)s_args->player.y + 1][(int)s_args->player.x] != '1')
		++s_args->player.y;
	return (1);
}

int		move_west(t_args *s_args)
{
	if (s_args->map[(int)s_args->player.y][(int)s_args->player.x - 1] != '1')
		--s_args->player.x;
	return (1);
}

int		move_east(t_args *s_args)
{
	if (s_args->map[(int)s_args->player.y][(int)s_args->player.x + 1] != '1')
		++s_args->player.x;
	return (1);
}