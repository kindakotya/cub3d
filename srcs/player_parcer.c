
#include "cub3d.h"

static int		set_pos(int c, t_player *player, int y, int x)
{
	if (c == 'N' || c == 'W' || c == 'S' || c == 'E')
	{
		player->x = x;
		player->y = y;
		return (1);
	}
	return (0);
}

static void		set_aov(t_player *player, char cp)
{
	player->angles[0] = 1.5 * M_PI;
	player->angles[1] = 1.75 * M_PI;
	player->angles[2] = 2. * M_PI;
	player->angles[3] = M_PI_4;
	player->angles[4] = M_PI_2;
	player->angles[5] = 0.75 * M_PI;
	player->angles[6] = M_PI;
	player->angles[7] = 1.25 * M_PI;
	if (cp == 'N')
		player->aov = 0;
	else if (cp == 'S')
		player->aov = 4;
	else if (cp == 'E')
		player->aov = 2;
	else if (cp == 'W')
		player->aov = 6;
}

t_player		ft_find_player(t_args *s_args)
{
	int			i;
	int			j;
	t_player	player;

	i = 0;
	while (s_args->map[i])
	{
		j = 0;
		while (s_args->map[i][j])
			set_pos(s_args->map[i][j], &player, i, j++);
		set_pos(s_args->map[i][j], &player, i++, j);
	}
	if (!player.x)
	{
		perror("There is no player on map.\n");
		ft_exit(s_args, 0);
	}
	set_aov(&player, s_args->map[i][j]);
	s_args->map[i][j] = '0';
	return (player);
}
