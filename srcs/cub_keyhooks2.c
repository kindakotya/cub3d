/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_keyhooks2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 16:57:55 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/02 02:02:42 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_arrow_left_pressed(t_args *s_args)
{
	if (fabs(s_args->player.aov - AOV_N) < 0.001)
		s_args->player.aov = AOV_W;
	else if (fabs(s_args->player.aov - AOV_W) < 0.001)
		s_args->player.aov = AOV_S;
	else if (fabs(s_args->player.aov - AOV_S) < 0.001)
		s_args->player.aov = AOV_E;
	else if (fabs(s_args->player.aov - AOV_E) < 0.001)
		s_args->player.aov = AOV_E - M_PI / 4;
	else if (fabs(s_args->player.aov - AOV_E + M_PI / 4) < 0.001)
		s_args->player.aov = AOV_N;
}

void	key_arrow_rigth_pressed(t_args *s_args)
{
	if (fabs(s_args->player.aov - AOV_N) < 0.001)
		s_args->player.aov = AOV_E;
	else if (fabs(s_args->player.aov - AOV_E) < 0.001)
		s_args->player.aov = AOV_S;
	else if (fabs(s_args->player.aov - AOV_S) < 0.001)
		s_args->player.aov = AOV_W;
	else if (fabs(s_args->player.aov - AOV_W) < 0.001)
		s_args->player.aov = AOV_N;
}