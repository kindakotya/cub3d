/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_parcer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 03:34:15 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/23 17:45:19 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

void		get_map_res(t_args *s_args, int fd)
{
	int i;
	int j;

	i = 0;
	while (s_args->map[i])
	{
		j = 0;
		while (s_args->map[i][j])
		{
			if (j >= s_args->map_w && s_args->map[i][j] != ' ')
				s_args->map_w = j + 1;
				++j;
		}
		++i;
	}
	s_args->map_h = i;
	if (s_args->map_h < 3 && s_args->map_w < 3)
	{
		perror("Map too small.");
		ft_exit(fd, s_args, 0, 6);
	}
}

int		get_res(char *line, t_args *s_args)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (!ft_isdigit(line[i]) && line[i] != ' ')
			return (-1);
		++i;
	}
	skip_spaces(&line);
	if (!ft_isdigit(*line))
		return (-1);
	s_args->win_w = ft_atoi(line);
	skip_numbers(&line);
	skip_spaces(&line);
	if (!ft_isdigit(*line))
		return (-1);
	s_args->win_h = ft_atoi(line);
	return (1);
}

int		get_path(char **path, char *line)
{
	int i;

	skip_spaces(&line);
	i = 0;
	while (line[i])
		if (ft_isspace(line[i++]))
			return (-1);
	*path = ft_strdup(line);
	if (path == NULL)
	{
		perror("Malloc error.\n");
		return (-1);
	}
	return (1);
}

int		get_color(char *line, unsigned int *color)
{
	skip_spaces(&line);
	if (!ft_isdigit(*line))
		return (-1);
	*color += ft_atoi(line) << 16;
	skip_numbers(&line);
	line = ft_strnstr(line, ",", 1);
	if (line == NULL)
		return (-1);
	++line;
	skip_spaces(&line);
	if (!ft_isdigit(*line))
		return (-1);
	*color += ft_atoi(line) << 8;
	skip_numbers(&line);
	line = ft_strnstr(line, ",", 1);
	if (line == NULL)
		return (-1);
	++line;
	skip_spaces(&line);
	if (!ft_isdigit(*line))
		return (-1);
	*color += ft_atoi(line);
	return (1);
}