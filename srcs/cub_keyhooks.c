/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_keyhooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 16:51:03 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/30 05:01:50 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	tex_push(t_args *s_args)
{
	if (s_args->map[(int)s_args->player.y]
		[(int)(s_args->player.x + 0.2)] == '1')
		s_args->player.x -= 0.1;
	if (s_args->map[(int)s_args->player.y]
		[(int)(s_args->player.x - 0.2)] == '1')
		s_args->player.x += 0.1;
	if (s_args->map[(int)(s_args->player.y + 0.2)]
		[(int)s_args->player.x] == '1')
		s_args->player.y -= 0.1;
	if (s_args->map[(int)(s_args->player.y - 0.2)]
		[(int)s_args->player.x] == '1')
		s_args->player.y += 0.1;
}

static void	step(t_args *s_args, double angle)
{
	double	x;
	double	y;
	double	step_x;
	double	step_y;

	step_x = 0.25 * cos(angle);
	step_y = 0.25 * sin(angle);
	x = s_args->player.x + step_x;
	y = s_args->player.y + step_y;
	if (s_args->map[(int)(y)][(int)(x)] != '1'
		&& s_args->map[(int)(y + step_y)][(int)(x + step_x)] != '1')
	{
		s_args->player.x = x;
		s_args->player.y = y;
	}
	tex_push(s_args);
}

int	key_pressed(int keycode, t_all *s_all)
{
	if (keycode == KEY_A)
		step(s_all->s_args, s_all->s_args->player.aov - M_PI_2);
	else if (keycode == KEY_D)
		step(s_all->s_args, s_all->s_args->player.aov + M_PI_2);
	else if (keycode == KEY_W)
		step(s_all->s_args, s_all->s_args->player.aov);
	else if (keycode == KEY_S)
		step(s_all->s_args, s_all->s_args->player.aov + M_PI);
	else if (keycode == KEY_ARROW_LEFT || keycode == KEY_Q)
		s_all->s_args->player.aov -= 0.26179938779;
	else if (keycode == KEY_ARROW_RIGTH || keycode == KEY_E)
		s_all->s_args->player.aov += 0.26179938779;
	else if (keycode == KEY_F12 && s_all->s_args->screenshot)
		screenshot(s_all->s_args, s_all->s_mlx);
	else if (keycode == KEY_ESC)
		ft_exit(0, s_all->s_args, s_all->s_mlx, 0);
	raycast(s_all);
	minimap(s_all->s_args, s_all->s_mlx);
	return (1);
}
