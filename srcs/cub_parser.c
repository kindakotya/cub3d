/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 16:44:34 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/09 00:32:44 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	set_aov(t_player *player, char cp)
// {
// 	player->angles[0] = 1.5 * M_PI;
// 	player->angles[1] = 1.75 * M_PI;
// 	player->angles[2] = 2. * M_PI;
// 	player->angles[3] = M_PI_4;
// 	player->angles[4] = M_PI_2;
// 	player->angles[5] = 0.75 * M_PI;
// 	player->angles[6] = M_PI;
// 	player->angles[7] = 1.25 * M_PI;
// 	if (cp == 'N')
// 		player->aov = 0;
// 	else if (cp == 'S')
// 		player->aov = 4;
// 	else if (cp == 'E')
// 		player->aov = 2;
// 	else if (cp == 'W')
// 		player->aov = 6;
// }

// t_player			ft_find_player(t_args *s_args)
// {
// 	int i;
// 	int j;
// 	t_player player;

// 	i = 0;
// 	while (s_args->map[i])
// 	{
// 		j = 0;
// 		while (s_args->map[i][j])
// 			if (s_args->map[i][j] == 'N' || s_args->map[i][j] == 'W' ||
// 				s_args->map[i][j] == 'S' || s_args->map[i][j] == 'E')
// 				break ;
// 			else
// 				++j;
// 		if (s_args->map[i][j] == 'N' || s_args->map[i][j] == 'W' ||
// 				s_args->map[i][j] == 'S' || s_args->map[i][j] == 'E')
// 				break ;
// 			else
// 				++i;
// 	}
// 	player.x = j;
// 	player.y = i;
// 	set_aov(&player, s_args->map[i][j]);
// 	s_args->map[i][j] = '0';
// 	return (player);
// }



int		get_res(char *line, t_args *s_args)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (!ft_isalnum(line[i]) && line[i] != ' ')
			return (-1);
		++i;
	}
	skip_spaces(&line);
	if (!ft_isalnum(*line))
		return (-1);
	s_args->win_w = ft_atoi(line);
	skip_numbers(&line);
	skip_spaces(&line);
	if (!ft_isalnum(*line))
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
	if ((*path = ft_strdup(line)) == NULL)
	{
		perror("Malloc error.\n");
		return (-1);
	}
	return (1);
}

int		get_color(char *line, unsigned int *color)
{
	skip_spaces(&line);
	if (!ft_isalnum(*line))
		return (-1);
	*color += ft_atoi(line) << 16;
	skip_numbers(&line);
	if ((line = ft_strnstr(line, ",", 1)) == NULL)
		return (-1);
	++line;
	skip_spaces(&line);
	if (!ft_isalnum(*line))
		return (-1);
	*color += ft_atoi(line) << 8;
	skip_numbers(&line);
	if ((line = ft_strnstr(line, ",", 1)) == NULL)
		return (-1);
	++line;
	skip_spaces(&line);
	if (!ft_isalnum(*line))
		return (-1);
	*color += ft_atoi(line);
	return (1);
}

int		parce_cub(t_args *s_args, char *line, char check[8])
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
	return (1);
}

int				check_all(char check[8])
{
	int i;

	i = 0;
	if (check[0] == -1)
		perror("Resolution is wrong.\n");
	if (check[1] == -1)
		perror("Path to the north texture is wrong.\n");
	if (check[2] == -1)
		perror("Path to the south texture is wrong.\n");
	if (check[3] == -1)
		perror("Path to the east texture is wrong.\n");
	if (check[4] == -1)
		perror("Path to the west texture is wrong.\n");
	if (check[5] == -1)
		perror("Path to the sprite is wrong.\n");
	if (check[6] == -1)
		perror("Floor color is wrong.\n");
	if (check[7] == -1)
		perror("Ceil color is wrong.\n");
	while (i <= 7)
		if (check[i] == -1)
			exit(-1);
		else if (!check[i++])
			return (0);
	return (1);
}

static int		read_file(int fd, t_args *s_args, char check[8])
{
	char *line;
	int i;
	int meow;

	meow = 0;
	while ((i = get_next_line(fd, &line)) == 1)
	{
		if (*line)
			parce_cub(s_args, line, check);
		free(line);
		if (check_all(check))
			break ;
	}
	if (i == -1)
	{
		perror("Can't read file.\n");
		exit(-1); //ft_exit
	}
	if (check_all(check) == 1)
			parce_map(s_args, fd);
		else if (check_all(check) == -1)
			exit(-1);
	return (1);
}

int getparam(char *str, t_args *s_args)
{
	int fd;
	int i;
	char check[8];

	i = 0;
	while (i < 8)
		check[i++] = 0;
	if ((fd = open(str, O_RDONLY)) == -1)
	{
		perror("Can't open file, friend.\n");
		exit(-1);
	}
	read_file(fd, s_args, check);
	close(fd);
	return (1);
}
