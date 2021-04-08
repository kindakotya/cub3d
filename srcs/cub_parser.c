/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 16:44:34 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/08 02:59:31 by gmayweat         ###   ########.fr       */
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
int		get_res(t_args *s_args, char *line)
{
	int i;

	i = 0;
	while (line[i])
		if (!ft_isalnum(line[i]) && line[i++] != ' ')
			return (-1);
	while (*line == ' ')
		++line;
	s_args->win_w = ft_atoi(line);
	++line;
	if (!ft_isalnum(*line))
		return (-1);
	s_args->win_h = ft_atoi(line);
	return (1);
}

int		get_path(char **path, char *line)
{
	int i;

	while (*line == ' ')
		++line;
	i = 0;
	while (line[i])
		++i;
	i = 0;
	while (line[i])
		if (ft_isspace(line[i++]))
			return (-1);
	*path = malloc((i + 1) * sizeof(char));
	while (line[i])
	{
		*path[i] = line[i];
		++i;
	}
	return (1);
}

int		get_color(int *color, char *line)
{
	while (*line == ' ')
		++line;
	if (ft_isalnum(*line))
		*color += ft_atoi(*line) << 16;
	else
		return (-1);
	if (ft_strnstr(line, ", ", 2) == line)
		line += 2;
	else
		return (-1);
	if (ft_isalnum(*line))
		*color += ft_atoi(*line) << 8;
	else
		return (-1);
	if (ft_strnstr(line, ", ", 2) == line)
		line += 2;
	else
		return (-1);
	if (ft_isalnum(*line))
		*color += ft_atoi(*line);
	else
		return (-1);
	return (1);
}

int		parce_cub(t_args *s_args, char *line, int check[8])
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
		check[6] = get_color(&s_args->floor, line + 1);
	else if (ft_strnstr(line, "C ", 2))
		check[7] = get_color(&s_args->ceil, line + 1);
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

char			**add_string(char **arr1, char *str)
{
	char **arr2;
	int i;

	i = 0;
	while (arr1[i])
		++i;
	if (arr2 = malloc((i + 2) * sizeof(char*)) == NULL)
	{
		perror("Malloc error.\n");
		exit(-1);
	}
	i = 0;
	while (arr1[i])
	{
		arr2[i] = arr1[i];
		++i;
	}
	arr2[i] = str;
	arr2[i + 1] = NULL;
	free(arr1);
	return (arr2);
}

void get_map_res(t_args *s_args)
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
	}
	s_args->map_h = i;
	if (s_args->map_h < 3 && s_args->map_w < 3)
	{
		perror("Map too small.");
		exit(-1);
	}
}

// int				left_dir(t_args *s_args, int *i, int *j)
// {
// 	if (*j != 0 && s_args->map[*i][*j - 1] == '1')
// 	{
// 		--(*j);
// 		return ('l');
// 	}
// 	else if (*i != 0 && s_args->map[*i - 1][*j] == '1')
// 	{
// 		--(*i);
// 		return ('u');
// 	}
// 		else if (*i != s_args->map_h && s_args->map[*i + 1][*j] == '1')
// 	{
// 		++(*i);
// 		return ('d');
// 	}
// 	return (0);
// }

// int				rigth_dir(t_args *s_args, int *i, int *j)
// {
// 	if (*j != s_args->map_w && s_args->map[*i][*j + 1] == '1')
// 	{
// 		++(*j);
// 		return ('r');
// 	}
// 	else if (*i != s_args->map_h && s_args->map[*i + 1][*j] == '1')
// 	{
// 		++(*i);
// 		return ('d');
// 	}
// 		else if (*i != 0 && s_args->map[*i - 1][*j] == '1')
// 	{
// 		--(*i);
// 		return ('u');
// 	}
// 	return (0);
// }

// int				up_dir(t_args *s_args, int *i, int *j)
// {
// 	if (*i != 0 && s_args->map[*i - 1][*j] == '1')
// 	{
// 		--(*i);
// 		return ('u');
// 	}
// 	else if (*j != s_args->map_w && s_args->map[*i][*j + 1] == '1')
// 	{
// 		++(*j);
// 		return ('r');
// 	}
// 	else if (*j != 0 && s_args->map[*i][*j - 1] == '1')
// 	{
// 		--(*j);
// 		return ('l');
// 	}
// 	return (0);
// }

// int				down_dir(t_args *s_args, int *i, int *j)
// {
// 	if (*i != 0 && s_args->map[*i + 1][*j] == '1')
// 	{
// 		++(*i);
// 		return ('d');
// 	}
// 	else if (*j != s_args->map_w && s_args->map[*i][*j + 1] == '1')
// 	{
// 		++(*j);
// 		return ('r');
// 	}
// 	else if (*j != 0 && s_args->map[*i][*j - 1] == '1')
// 	{
// 		--(*j);
// 		return ('l');
// 	}
// 	return (0);
// }
int				check_y(char **map, int space_x, int space_y)
{
	int walls;

	walls = 0;
	while (space_y)
	{
		if (map[space_y--][space_x] == '1')
		{
			++walls;
			break ;
		}
	}
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

int				check_x(char **map, int space_x, int space_y)
{
	int walls;

	walls = 0;
	while (space_x)
	{
		if (map[space_y][space_x--] == '1')
		{
			++walls;
			break ;
		}
	}
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
int				find_walls(char **map, int space_x, int space_y)
{
	if ()
	{
		
	return (1);
}

int				check_map(t_args *s_args)
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
		}
	}
	return (1);
}
int				parce_map(t_args *s_args, int fd)
{
	int i;
	char *line;

	while (i = get_next_line(fd, &line) == 1)
		if (*line == '\n')
			free(line);
		else
			break ;
	if (s_args->map = malloc(2 * sizeof(char*) == 0))
	{
		perror("Malloc error.\n");
		exit(-1);
	}
	s_args->map[0] = line;
	s_args->map[1] = NULL;
	while (i = get_next_line(fd, &line) == 1)
		s_args->map = add_string(s_args->map, line);
	get_map_res(s_args);
	if (!check_map(s_args))
		exit(-1);
}

static int		read_file(int fd, t_args *s_args, int check[8])
{
	char *line;
	int i;
	int meow;

	meow = 0;
	while (i = get_next_line(fd, &line) == 1)
	{
		if (*line != '\n')
			parce_cub(s_args, line, check);
		free(line);
		if (check_all(check))
			break ;
	}
	if (i == -1)
	{
		perror("Can't read map.\n");
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
	int check[9];

	fd = 0;
	while (fd < 9)
		check[fd++] = 0;
	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		perror("Can't open file, friend.\n");
		exit(-1);
	}
	read_file(fd, s_args, check);
	close(fd);
	return (1);
}
