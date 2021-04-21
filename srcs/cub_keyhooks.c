/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_keyhooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 16:51:03 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/21 03:55:55 by gmayweat         ###   ########.fr       */
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

void		step(t_args *s_args, double angle)
{
	double x;
	double y;
	double cosx;
	double siny;
	double wall[2];

	wall[0] = MEOW;
	wall[1] = MEOW;
	cosx = MEOW * cos(angle);
	siny = MEOW * sin(angle);
	if (cosx < 0)
		wall[0] = -MEOW;
	if (siny < 0)
		wall[1] = -MEOW;
	x = s_args->player.x + cosx;
	y = s_args->player.y + siny;
	if (s_args->map[(int)(y)][(int)(x)] != '1' 
		&& s_args->map[(int)(y + wall[1])][(int)(x + wall[0])] != '1')
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

void	sort_keys(int keycode, t_loop *s_hook)
{
	if (keycode == KEY_A)
		step(s_hook->s_args, s_hook->s_args->player.aov - M_PI_2);
	else if (keycode == KEY_D)
		step(s_hook->s_args, s_hook->s_args->player.aov + M_PI_2);
	else if (keycode == KEY_W)
		step(s_hook->s_args, s_hook->s_args->player.aov);
	else if (keycode == KEY_S)
		step(s_hook->s_args, s_hook->s_args->player.aov + M_PI);
	else if (keycode == KEY_ARROW_LEFT || keycode == KEY_Q)
		s_hook->s_args->player.aov -= 0.26179938779;
	else if (keycode == KEY_ARROW_RIGTH || keycode == KEY_E)
		s_hook->s_args->player.aov += 0.26179938779;
	else if (keycode == KEY_F12 && s_hook->s_args->screenshot)
		screenshot(s_hook->s_args, s_hook->s_mlx);
	else if (keycode == KEY_ESC)
		ft_exit(0, s_hook->s_args, s_hook->s_mlx, 0);
}

int key_pressed(int keycode, t_loop *s_hook)
{
	static char c = '0';

	if (s_hook->s_args->
		map[(int)s_hook->s_args->player.y][(int)s_hook->s_args->player.x] != c)
		s_hook->s_args->
		map[(int)s_hook->s_args->player.y][(int)s_hook->s_args->player.x] = c;
	sort_keys(keycode, s_hook);
	if (c != s_hook->s_args->
		map[(int)s_hook->s_args->player.y][(int)s_hook->s_args->player.x])
		c = s_hook->s_args->
		map[(int)s_hook->s_args->player.y][(int)s_hook->s_args->player.x];
	map(s_hook->s_args, s_hook->s_mlx);
	raycast(s_hook->s_args, s_hook->s_mlx);
	draw_minimap(s_hook->s_args, s_hook->s_mlx);
	return (1);
}
