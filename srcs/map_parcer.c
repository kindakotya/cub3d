/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parcer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 00:22:44 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/09 00:28:23 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		get_map_res(t_args *s_args)
{
	int i;
	int j;

	i = 0;
	while (s_args->map[i])
	{
		j = 0;
		while (s_args->map[i][j])
		{
			if (j > s_args->map_w || s_args->map[i][j] != ' ')
				s_args->map_w = j + 1;
			++j;
		}
		++i;
	}
	s_args->map_h = i;
	if (s_args->map_h < 3 && s_args->map_w < 3)
	{
		perror("Map too small.");
		exit(-1);
	}
}

static int		check_y(char **map, int space_x, int space_y)
{
	int walls;

	walls = 0;
	while (space_y >= 0)
	{
		if (map[space_y--][space_x] == '1')
		{
			++walls;
			break ;
		}
	}
	if (space_y < 0)
		space_y = 0;
	while (map[space_y])
	{
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

static int		check_x(char **map, int space_x, int space_y)
{
	int walls;

	walls = 0;
	while (space_x >= 0)
	{
		if (map[space_y][space_x--] == '1')
		{
			++walls;
			break ;
		}
	}
	if (space_x < 0)
		space_x = 0;
	while (map[space_y][space_x])
	{
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
			if (s_args->map[i][j] == '0')
				if (!check_x(s_args->map, j, i) && !check_y(s_args->map, j, i))
				{
					perror("Map is not valid.\n");
					exit(-1);
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
		if (*line == '\n')
			free(line);
		else
			break ;
	if ((s_args->map = malloc(2 * sizeof(char*))) == NULL)
	{
		perror("Malloc error.\n");
		exit(-1);
	}
	s_args->map[0] = line;
	s_args->map[1] = NULL;
	while ((i = get_next_line(fd, &line)) == 1)
		s_args->map = add_string(s_args->map, line);
	if (*line)
		s_args->map = add_string(s_args->map, line);
	else
		free(line);
	get_map_res(s_args);
	if (!check_map(s_args))
		exit(-1);
}