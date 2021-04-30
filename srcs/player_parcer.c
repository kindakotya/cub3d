/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_parcer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 03:34:24 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/29 18:08:27 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	set_pos(int c, t_player *player, int y, int x)
{
	if ((player->x > 1 || player->y > 1) && is_side_of_world(c))
		return (0);
	if (is_side_of_world(c))
	{
		player->x = x + 0.5;
		player->y = y + 0.5;
	}
	return (1);
}

static void	set_aov(t_player *player, char cp)
{
	if (cp == 'N')
		player->aov = 1.5 * M_PI;
	else if (cp == 'S')
		player->aov = M_PI_2;
	else if (cp == 'E')
		player->aov = 2. * M_PI;
	else if (cp == 'W')
		player->aov = M_PI;
}

t_player	find_player(t_args *s_args)
{
	int			i;
	int			j;
	t_player	player;

	i = 0;
	while (s_args->map[i])
	{
		j = 0;
		while (s_args->map[i][j])
		{
			if (set_pos(s_args->map[i][j], &player, i, j) == 0)
				ft_exit(0, s_args, 0, 7);
			++j;
		}
		++i;
	}
	if (player.x < 1 || player.y < 1)
		ft_exit(0, s_args, 0, 7);
	set_aov(&player, s_args->map[(int)player.y][(int)player.x]);
	s_args->map[(int)player.y][(int)player.x] = '0';
	return (player);
}
