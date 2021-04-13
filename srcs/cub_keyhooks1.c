/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_keyhooks1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 16:51:03 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/13 23:50:23 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MEOW 0.2
#include "cub3d.h"

void		key_a_pressed(t_args *s_args)
{
	double x;
	double y;

	x = s_args->player.x + MEOW * cos(s_args->player.a - M_PI_2);
	y = s_args->player.y + MEOW * sin(s_args->player.a - M_PI_2);
	if (s_args->map[(int)floor(y + 0.5)][(int)floor(x + 0.5)] != '1')
	{
		s_args->player.x = x;
		s_args->player.y = y;
	}
}

void		key_w_pressed(t_args *s_args)
{
	double x;
	double y;

	x = s_args->player.x + MEOW * cos(s_args->player.a);
	y = s_args->player.y + MEOW * sin(s_args->player.a);
	if (s_args->map[(int)floor(y + 0.5)][(int)floor(x + 0.5)] != '1')
	{
		s_args->player.x = x;
		s_args->player.y = y;
	}
	//s_args->player.x = (s_args->player.x 
	// if (s_args->player.aov == 0)
	// 	move_north(s_args);
	// else if (s_args->player.aov == 1)
	// 	move_north(s_args) && move_east(s_args);
	// else if (s_args->player.aov == 2)
	// 	move_east(s_args);
	// else if (s_args->player.aov == 3)
	// 	move_east(s_args) && move_south(s_args);
	// else if (s_args->player.aov == 4)
	// 	move_south(s_args);
	// else if (s_args->player.aov == 5)
	// 	move_south(s_args) && move_west(s_args);
	// else if (s_args->player.aov == 6)
	// 	move_west(s_args);
	// else if (s_args->player.aov == 7)
	// 	move_west(s_args) && move_north(s_args);
}

void		key_d_pressed(t_args *s_args)
{
	double x;
	double y;

	x = s_args->player.x + MEOW * cos(s_args->player.a + M_PI_2);
	y = s_args->player.y + MEOW * sin(s_args->player.a + M_PI_2);
	if (s_args->map[(int)floor(y + 0.5)][(int)floor(x + 0.5)] != '1')
	{
		s_args->player.x = x;
		s_args->player.y = y;
	}
}

void		key_s_pressed(t_args *s_args)
{
	double x;
	double y;

	x = s_args->player.x + MEOW * cos(s_args->player.a + M_PI);
	y = s_args->player.y + MEOW * sin(s_args->player.a + M_PI);
	if (s_args->map[(int)floor(y + 0.5)][(int)floor(x + 0.5)] != '1')
	{
		s_args->player.x = x;
		s_args->player.y = y;
	}
}

int key_pressed(int keycode, t_loop *s_hook)
{
	static char c = '0';

	s_hook->s_args->
	map[(int)s_hook->s_args->player.y][(int)s_hook->s_args->player.x] = c;
	if (keycode == KEY_A)
		key_a_pressed(s_hook->s_args);
	else if (keycode == KEY_D)
		key_d_pressed(s_hook->s_args);
	else if (keycode == KEY_W)
		key_w_pressed(s_hook->s_args);
	else if (keycode == KEY_S)
		key_s_pressed(s_hook->s_args);
	else if (keycode == KEY_ARROW_LEFT)
		key_arrow_left_pressed(s_hook);
	else if (keycode == KEY_ARROW_RIGTH)
		key_arrow_rigth_pressed(s_hook->s_args);
	else if (keycode == KEY_ESC)
		ft_exit(0, s_hook->s_args, s_hook->s_mlx, 0);
	c = s_hook->s_args->
	map[(int)s_hook->s_args->player.y][(int)s_hook->s_args->player.x];
	map(s_hook->s_args, s_hook->s_mlx);
	raycast(s_hook->s_args, s_hook->s_mlx);
	draw_minimap(s_hook->s_args, s_hook->s_mlx);
	return (1);
}
