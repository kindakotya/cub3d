/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parcer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 00:22:44 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/30 18:28:58 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_y(char **map, int zero_x, int zero_y, int walls)
{
	while (map[zero_y])
	{
		if (!is_valid_char(map[zero_y][zero_x]))
			break ;
		if (map[zero_y++][zero_x] == '1')
		{
			++walls;
			break ;
		}
	}
	--zero_y;
	while (zero_y > 0)
	{
		if (!is_valid_char(map[zero_y][zero_x]))
			break ;
		if (map[--zero_y][zero_x] == '1')
		{
			++walls;
			break ;
		}
	}
	if (walls == 2)
		return (1);
	return (0);
}

static int	check_x(char **map, int zero_x, int zero_y, int walls)
{
	while (map[zero_y][zero_x])
	{
		if (!is_valid_char(map[zero_y][zero_x]))
			break ;
		if (map[zero_y][zero_x++] == '1')
		{
			++walls;
			break ;
		}
	}
	--zero_x;
	while (zero_x > 0)
	{
		if (!is_valid_char(map[zero_y][zero_x]))
			break ;
		if (map[zero_y][--zero_x] == '1')
		{
			++walls;
			break ;
		}
	}
	if (walls == 2)
		return (1);
	return (0);
}

static int	check_map(t_args *s_args)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (s_args->map[y])
	{
		x = 0;
		while (s_args->map[y][x])
		{
			if (!is_valid_char(s_args->map[y][x]) && s_args->map[y][x] != ' ')
				return (0);
			if ((s_args->map[y][x] == '0'
				|| is_side_of_world(s_args->map[y][x]))
				&& (!check_x(s_args->map, x, y, 0)
				|| !check_y(s_args->map, x, y, 0)))
				return (0);
			++x;
		}
		++y;
	}
	return (1);
}

static void	load_map(t_args *s_args, int fd)
{
	int		i;
	char	*line;

	i = 1;
	while (i == 1)
	{
		i = get_next_line(fd, &line);
		if (i == -1)
			ft_exit(fd, s_args, 0, 4);
		if (*line)
			s_args->map = add_string(s_args->map, line);
		else
		{
			free(line);
			ft_exit(fd, s_args, 0, 8);
		}
		if (s_args->map == NULL)
			ft_exit(fd, s_args, 0, 2);
		if (i == 0)
			return ;
	}
}

void	parce_map(t_args *s_args, int fd, char **line)
{
	s_args->map = malloc(2 * sizeof(char *));
	if (s_args->map == NULL)
	{
		if (*line)
			free(*line);
		ft_exit(fd, s_args, 0, 2);
	}
	s_args->map[0] = *line;
	s_args->map[1] = NULL;
	load_map(s_args, fd);
	get_map_res(s_args, fd);
	if (!check_map(s_args))
		ft_exit(fd, s_args, 0, 8);
}
