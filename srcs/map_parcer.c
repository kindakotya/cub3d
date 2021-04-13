/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parcer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 00:22:44 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/11 16:31:03 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		check_y(char **map, int space_x, int space_y, int walls)
{
	while (space_y > 0)
	{
		if (!is_valid_char(map[--space_y][space_x]))
			break;
		if (map[space_y--][space_x] == '1')
		{
			++walls;
			break ;
		}
	}
	while (map[space_y])
	{
		if (!is_valid_char(map[space_y][space_x]))
			break;
		if (map[++space_y][space_x] == '1')
		{
			++walls;
			break ;
		}
	}
	if (walls == 2)
		return (1);
	return (0);
}

static int		check_x(char **map, int space_x, int space_y, int walls)
{
	while (space_x > 0)
	{
		if (!is_valid_char(map[space_y][space_x]))
			break;
		if (map[space_y][--space_x] == '1')
		{
			++walls;
			break ;
		}
	}
	while (map[space_y][space_x])
	{
		if (!is_valid_char(map[space_y][space_x]))
			break;
		if (map[space_y][++space_x] == '1')
		{
			++walls;
			break ;
		}
	}
	if (walls == 2)
		return (1);
	return (0);
}

static int		check_map(t_args *s_args)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s_args->map[i])
	{
		j = 0;
		while (s_args->map[i][j])
		{
			if ((s_args->map[i][j] == '0' || 
			is_side_of_world(s_args->map[i][j])) && 
			!check_x(s_args->map, j, i, 0) && !check_y(s_args->map, j, i, 0))
				return (0);
			++j;
		}
		++i;
	}
	return (1);
}

static void		load_map(t_args *s_args, int fd)
{
	int i;
	char *line;

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

void			parce_map(t_args *s_args, int fd, char **line)
{
	int i;

	s_args->map = malloc(2 * sizeof(char*));
	if (s_args->map == NULL)
	{
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