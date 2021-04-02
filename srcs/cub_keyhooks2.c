/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_keyhooks2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 16:57:55 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/02 19:03:21 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_arrow_left_pressed(t_args *s_args)
{
	if (s_args->player.aov == 0)
		s_args->player.aov = 7;
	else
		--s_args->player.aov;
}

void	key_arrow_rigth_pressed(t_args *s_args)
{
	if (s_args->player.aov == 7)
		s_args->player.aov = 0;
	else
		++s_args->player.aov;
}