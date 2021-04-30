/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 19:45:54 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/30 02:44:39 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	red_cross(t_all *s_all)
{
	ft_exit(0, s_all->s_args, s_all->s_mlx, 0);
	return (0);
}

void	cub_init(char **input, int save)
{
	t_all	s_all;
	t_args	s_args;
	t_mlx	s_mlx;

	clear_args(&s_args);
	getparam(input[1], &s_args);
	if (save == 2)
		s_args.screenshot = input[3];
	s_mlx = start_mlx(&s_args);
	s_all.s_args = &s_args;
	s_all.s_mlx = &s_mlx;
	raycast(&s_all);
	mlx_put_image_to_window(s_mlx.mlx, s_mlx.win, s_mlx.img.img, 0, 0);
	if (save == 1)
	{
		s_args.screenshot = "first_rendered_image.bmp";
		screenshot(&s_args, &s_mlx);
	}
	minimap(&s_args, &s_mlx);
	mlx_hook(s_mlx.win, 2, 1, &key_pressed, &s_all);
	mlx_hook(s_mlx.win, 17, 0, &red_cross, &s_all);
	mlx_loop(s_mlx.mlx);
}
