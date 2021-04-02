/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_keyhooks1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 16:51:03 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/02 19:36:08 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		key_a_pressed(t_args *s_args)
{
	if (s_args->player.aov == 0)
		move_west(s_args);
	else if (s_args->player.aov == 1)
		move_west(s_args) && move_north(s_args);
	else if (s_args->player.aov == 2)
		move_north(s_args);
	else if (s_args->player.aov == 3)
		move_north(s_args) && move_east(s_args);
	else if (s_args->player.aov == 4)
		move_east(s_args);
	else if (s_args->player.aov == 5)
		move_west(s_args) && move_south(s_args);
	else if (s_args->player.aov == 6)
		move_south(s_args);
	else if (s_args->player.aov == 7)
		move_south(s_args) && move_west(s_args);
}

void		key_w_pressed(t_args *s_args)
{
	if (fabs(s_args->player.aov - AOV_N) < 0.001)
	{
		if (s_args->map[s_args->player.y - 1][s_args->player.x] == '0')
			--s_args->player.y;
	}
	else if (fabs(s_args->player.aov - AOV_S) < 0.001)
	{
		if (s_args->map[s_args->player.y + 1][s_args->player.x] == '0')
			++s_args->player.y;
	}
	else if (fabs(s_args->player.aov - AOV_W) < 0.001)
	{
		if (s_args->map[s_args->player.y][s_args->player.x - 1] == '0')
		--s_args->player.x;
	}
	else if (fabs(s_args->player.aov - AOV_E) < 0.001)
		if (s_args->map[s_args->player.y][s_args->player.x + 1] == '0')
			++s_args->player.x;
}

void		key_d_pressed(t_args *s_args)
{
	if (fabs(s_args->player.aov - AOV_N) < 0.001)
	{
		if (s_args->map[s_args->player.y][s_args->player.x + 1] == '0')
			++s_args->player.x;
	}
	else if (fabs(s_args->player.aov - AOV_S) < 0.001)
	{
		if (s_args->map[s_args->player.y][s_args->player.x - 1] == '0')
			--s_args->player.x;
	}
	else if (fabs(s_args->player.aov - AOV_W) < 0.001)
	{
		if (s_args->map[s_args->player.y - 1][s_args->player.x] == '0')
		--s_args->player.y;
	}
	else if (fabs(s_args->player.aov - AOV_E) < 0.001)
		if (s_args->map[s_args->player.y + 1][s_args->player.x] == '0')
			++s_args->player.y;
}

void		key_s_pressed(t_args *s_args)
{
	if (fabs(s_args->player.aov - AOV_N) < 0.001)
	{
		if (s_args->map[s_args->player.y + 1][s_args->player.x] == '0')
			++s_args->player.y;
	}
	else if (fabs(s_args->player.aov - AOV_S) < 0.001)
	{
		if (s_args->map[s_args->player.y - 1][s_args->player.x] == '0')
			--s_args->player.y;
	}
	else if (fabs(s_args->player.aov - AOV_W) < 0.001)
	{
		if (s_args->map[s_args->player.y][s_args->player.x + 1] == '0')
		++s_args->player.x;
	}
	else if (fabs(s_args->player.aov - AOV_E) < 0.001)
		if (s_args->map[s_args->player.y][s_args->player.x - 1] == '0')
			--s_args->player.x;
}

int key_pressed(int keycode, t_loop *s_hook)
{
	if (keycode == KEY_A)
		key_a_pressed(s_hook->s_args);
	else if (keycode == KEY_D)
		key_d_pressed(s_hook->s_args);
	else if (keycode == KEY_W)
		key_w_pressed(s_hook->s_args);
	else if (keycode == KEY_S)
		key_s_pressed(s_hook->s_args);
	else if (keycode == KEY_ARROW_LEFT)
		key_arrow_left_pressed(s_hook->s_args);
	else if (keycode == KEY_ARROW_RIGTH)
		key_arrow_rigth_pressed(s_hook->s_args);
	else if (keycode == KEY_ESC)
		ft_exit(s_hook->s_args, s_hook->s_mlx);

		map(s_hook->s_args, s_hook->s_mlx);
	raycast(s_hook->s_args, s_hook->s_mlx);
		draw_minimap(s_hook->s_args, s_hook->s_mlx);

	return (1);
}