/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parcer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 00:22:44 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/09 04:16:48 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		is_valid_char(int c)
{
	if (c == '0' || c == '1' || c == '2' || is_side_of_world(c))
		return (1);
	return (0);
}

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
			{
				perror("Map is not valid.\n");
				return (-1);
			}
			++j;
		}
		++i;
	}
	return (1);
}

void			parce_map(t_args *s_args, int fd)
{
	int i;
	char *line;

	while ((i = get_next_line(fd, &line)) == 1)
		if (*line == '\0')
			free(line);
		else
			break ;
	if ((s_args->map = malloc(2 * sizeof(char*))) == NULL)
	{
		perror("Malloc error.\n");
		ft_exit(fd, s_args, 0, -1);
	}
	s_args->map[0] = line;
	s_args->map[1] = NULL;
	while ((i = get_next_line(fd, &line)) == 1)
		s_args->map = add_string(s_args->map, line);
	if (*line)
		s_args->map = add_string(s_args->map, line);
	else
		free(line);
	get_map_res(s_args, fd);
	if (!check_map(s_args))
		ft_exit(fd, s_args, 0, -1);
}