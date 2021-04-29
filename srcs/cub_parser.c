/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 16:44:34 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/29 03:26:45 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parce_cub(t_args *s_args, char *line, char check[8])
{
	if (ft_strnstr(line, "R ", 2))
		check[0] = get_res(line + 1, s_args);
	else if (ft_strnstr(line, "NO ", 3))
		check[1] = get_path(&s_args->tex_no.path, line + 2);
	else if (ft_strnstr(line, "SO ", 3))
		check[2] = get_path(&s_args->tex_so.path, line + 2);
	else if (ft_strnstr(line, "EA ", 3))
		check[3] = get_path(&s_args->tex_ea.path, line + 2);
	else if (ft_strnstr(line, "WE ", 3))
		check[4] = get_path(&s_args->tex_we.path, line + 2);
	else if (ft_strnstr(line, "S ", 2))
		check[5] = get_path(&s_args->sprite.path, line + 1);
	else if (ft_strnstr(line, "F ", 2))
		check[6] = get_color(line + 1, &s_args->floor);
	else if (ft_strnstr(line, "C ", 2))
		check[7] = get_color(line + 1, &s_args->ceil);
	else
		return (0);
	return (1);
}

static int	check_all(int fd, t_args *s_args, char check[8])
{
	int	i;

	i = 0;
	while (i <= 7)
	{
		if (check[i] == -1)
			ft_exit(fd, s_args, 0, i + 24);
		else if (!check[i++])
			return (0);
	}
	return (1);
}

static int	read_file(int fd, t_args *s_args, char check[8])
{
	char	*line;
	int		i;

	i = 1;
	while (i == 1)
	{
		i = get_next_line(fd, &line);
		if (i == -1 || i == 0)
			ft_exit(fd, s_args, 0, 4);
		if (check_all(fd, s_args, check) && *line)
			break ;
		if (*line)
		{
			if (parce_cub(s_args, line, check) == 0)
			{
				free(line);
				ft_exit(fd, s_args, 0, 9);
			}
		}
		free(line);
	}
	parce_map(s_args, fd, &line);
	return (1);
}

int	getparam(char *str, t_args *s_args)
{
	int		fd;
	int		i;
	char	check[8];

	i = 0;
	while (i < 8)
		check[i++] = 0;
	fd = open(str, O_RDONLY);
	if (fd == -1)
		ft_exit(fd, s_args, 0, 3);
	read_file(fd, s_args, check);
	close(fd);
	s_args->player = find_player(s_args);
	return (1);
}
