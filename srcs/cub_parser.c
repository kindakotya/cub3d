/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 21:31:38 by gmayweat          #+#    #+#             */
/*   Updated: 2021/02/25 23:04:46 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void ft_parceres(t_args *s_args, const char *arglist)
{
	char	*point;
	size_t	i;

	i = 0;
	point = ft_strchr(arglist, 'R');
	while (point[i] && point[i] != '\n')
	{
		++i;
		if (!s_args->res_x && ft_isalnum(point[i]))
		{
			s_args->res_x = ft_atoi(point + i);
			while (ft_isalnum(point[i]))
				++i;
        }
		if (s_args->res_x && ft_isalnum(point[i]))
			s_args->res_y = ft_atoi(point + i);
	}
}

static char*   ft_parcepath(const char *arglist, const char *side)
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
	while (point[i] && point[i] != '\n')
	{
		++j;
		++i;
	}
	path = malloc((j + 1) * sizeof(char));
	path[j] = '\0';
	while (j)
		path[j--] = point[i--];
	return (path);
}

static void		ft_parcecolor(t_args *s_args, char *arglist, char fc)
{
	char *point;

	point = ft_strchr(arglist, fc);
	if (fc == 'f')
	{
		s_args->floor_r = ft_atoi(point + 1);
		s_args->floor_g = ft_atoi(ft_strchr(point, ',') + 1);
		s_args->floor_b = ft_atoi(ft_strchr(
			ft_strchr(point, ',') + 1, ',') + 1);
	}
	else
	{
		s_args->ceil_r = ft_atoi(point + 1);
		s_args->ceil_g = ft_atoi(ft_strchr(point, ',') + 1);
		s_args->ceil_b = ft_atoi(ft_strchr(
			ft_strchr(point, ',') + 1, ',') + 1);
	}

}

int     ft_parcecub(t_args *s_args, char *arglist)
{
	ft_parceres(s_args, arglist);
	ft_parcecolor(s_args, arglist, 'F');
	ft_parcecolor(s_args, arglist, 'C');
	s_args->path_no = ft_parcepath(arglist, "NO");
	s_args->path_so = ft_parcepath(arglist, "SO");
	s_args->path_ea = ft_parcepath(arglist, "EA");
	s_args->path_we = ft_parcepath(arglist, "WE");
	s_args->path_s = ft_parcepath(arglist, "S");
	return (1);
}
