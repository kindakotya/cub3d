/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 21:31:38 by gmayweat          #+#    #+#             */
/*   Updated: 2021/03/22 01:18:48 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static void 		find_map_res(t_args *s_s_args)
{
	int i;
	int j;

	i = 0;
	while (s_s_args->map[i])
	{
		j = 0;
		while (s_s_args->map[i][j])
			++j;
		if (s_s_args->map_w < j)
			s_s_args->map_w = j - 1;
		++i;
	}
	s_s_args->map_h = i - 1;
}

static void		ft_parcemap(char *point, t_args *s_args)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (*point && *point != '\n')
		++point;
	while (*point && *point == '\n')
		++point;
	if (*point == ' ' || *point == '1')
	{
		s_args->map = ft_split(point, '\n');
		find_map_res(s_args);
	}
}

static void		ft_parceres(t_args *s_args, const char *arglist)
{
	char	*point;
	size_t	i;

	i = 0;
	point = ft_strchr(arglist, 'R');
	while (point[i] && point[i] != '\n')
	{
		++i;
		if (!s_args->win_w && ft_isalnum(point[i]))
		{
			s_args->win_w = ft_atoi(point + i);
			while (ft_isalnum(point[i]))
				++i;
        }
		if (s_args->win_w && ft_isalnum(point[i]) && !s_args->win_h)
			s_args->win_h = ft_atoi(point + i);
	}
	ft_parcemap(point, s_args);
}

static char*   ft_parcepath(t_args *s_args, const char *arglist, const char *side)
{
	size_t	i;
	size_t	j;
	char	*point;
	char	*path;

	i = 0;
	j = 0;
	point = ft_strnstr(arglist, side, ft_strlen(arglist)) + ft_strlen(side);
	while (point[i] && point[i] != '\n' && ft_isspace(point[i]))
		++i;
	while (point[i] && point[i + 1] != '\n')
	{
		++j;
		++i;
	}
	path = malloc((j + 1) * sizeof(char));
	path[j] = '\0';
	while (j)
		path[--j] = point[i--];
	ft_parcemap(point, s_args);
	return (path);
}

static void		ft_parcecolor(t_args *s_args, char *arglist, char fc)
{
	char *point;

	point = ft_strchr(arglist, fc);
	if (fc == 'F')
	{
		s_args->floor = (ft_atoi(point + 1) << 16) + 
			(ft_atoi(ft_strchr(point, ',')+ 1) << 8) + 
			ft_atoi(ft_strchr(ft_strchr(point, ',') + 1, ',') + 1);
	}
	else
	{
		s_args->ceil = (ft_atoi(point + 1) << 16) + 
			(ft_atoi(ft_strchr(point, ',')+ 1) << 8) + 
			ft_atoi(ft_strchr(ft_strchr(point, ',') + 1, ',') + 1);
	}
	ft_parcemap(point, s_args);
}

int     ft_parcecub(t_args *s_args, char *arglist)
{
	int i;

	i = 0;
	ft_parceres(s_args, arglist);
	ft_parcecolor(s_args, arglist, 'F');
	ft_parcecolor(s_args, arglist, 'C');
	s_args->path_no = ft_parcepath(s_args, arglist, "NO");
	s_args->path_so = ft_parcepath(s_args, arglist, "SO");
	s_args->path_ea = ft_parcepath(s_args, arglist, "EA");
	s_args->path_we = ft_parcepath(s_args, arglist, "WE");
	s_args->path_s = ft_parcepath(s_args, arglist, "S");
	s_args->win = malloc((s_args->win_h + 1) * sizeof(char*));
	s_args->win[s_args->win_h] = NULL;
	while (i < s_args->win_h)
		s_args->win[i++] = ft_calloc(s_args->win_w + 1, sizeof(char));
	return (1);
}
