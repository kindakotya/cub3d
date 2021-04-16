/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_keyhooks1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 16:51:03 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/16 15:05:43 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MEOW 0.25
#include "cub3d.h"

void		key_a_pressed(t_args *s_args)
{
	double x;
	double y;
	double cosx;
	double siny;
	cosx = MEOW * cos(s_args->player.aov - M_PI_2);
	siny = MEOW * sin(s_args->player.aov - M_PI_2);
	x = s_args->player.x + cosx;
	y = s_args->player.y + siny;
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
	double cosx;
	double siny;
	double wall[2];

	wall[0] = 0.5;
	wall[1] = 0.5;
	cosx = MEOW * cos(s_args->player.aov);
		siny = MEOW * sin(s_args->player.aov);
	if (cosx < 0)
		wall[0] = 0.5;
	if (siny < 0)
		wall[1] = 0.5;

	x = s_args->player.x + cosx;
	y = s_args->player.y + siny;
	double xx = floor(x + wall[0]);
	double yy = floor(y + wall[1]);
	if (s_args->map[(int)(yy)][(int)(xx)] != '1')
	{
		s_args->player.x = x;
		s_args->player.y = y;
	}
}

void		key_d_pressed(t_args *s_args)
{
	double x;
	double y;

	x = s_args->player.x + MEOW * cos(s_args->player.aov + M_PI_2);
	y = s_args->player.y + MEOW * sin(s_args->player.aov + M_PI_2);
	if (s_args->map[(int)floor(y * 1.05)][(int)floor(x * 1.05)] != '1')
	{
		s_args->player.x = x;
		s_args->player.y = y;
	}
}

void		key_s_pressed(t_args *s_args)
{
	double x;
	double y;

	x = s_args->player.x + MEOW * cos(s_args->player.aov + M_PI);
	y = s_args->player.y + MEOW * sin(s_args->player.aov + M_PI);
	if (s_args->map[(int)floor(y * 1.05)][(int)floor(x * 1.05)] != '1')
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
	else if (keycode == KEY_ARROW_LEFT || keycode == KEY_Q)
		key_arrow_left_pressed(s_hook);
	else if (keycode == KEY_ARROW_RIGTH || keycode == KEY_E)
		key_arrow_rigth_pressed(s_hook->s_args);
	else if (keycode == KEY_F12 && s_hook->s_args->screenshot)
		screenshot(s_hook->s_args, s_hook->s_mlx);
	else if (keycode == KEY_ESC)
		ft_exit(0, s_hook->s_args, s_hook->s_mlx, 0);
	c = s_hook->s_args->
	map[(int)s_hook->s_args->player.y][(int)s_hook->s_args->player.x];
	map(s_hook->s_args, s_hook->s_mlx);
	raycast(s_hook->s_args, s_hook->s_mlx);
	draw_minimap(s_hook->s_args, s_hook->s_mlx);
	return (1);
}
