/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 21:31:38 by gmayweat          #+#    #+#             */
/*   Updated: 2021/03/18 17:16:06 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		ft_parcemap(char *point, t_args *args)
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
		args->map = ft_writemap(point);
	}
}

static void		ft_parceres(t_args *args, const char *arglist)
{
	char	*point;
	size_t	i;

	i = 0;
	point = ft_strchr(arglist, 'R');
	while (point[i] && point[i] != '\n')
	{
		++i;
		if (!args->res_x && ft_isalnum(point[i]))
		{
			args->res_x = ft_atoi(point + i);
			while (ft_isalnum(point[i]))
				++i;
        }
		if (args->res_x && ft_isalnum(point[i]) && !args->res_y)
			args->res_y = ft_atoi(point + i);
	}
	ft_parcemap(point, args);
}

static char*   ft_parcepath(t_args *args, const char *arglist, const char *side)
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
		path[--j] = point[i--];
	ft_parcemap(point, args);
	return (path);
}

static void		ft_parcecolor(t_args *args, char *arglist, char fc)
{
	char *point;

	point = ft_strchr(arglist, fc);
	if (fc == 'F')
	{
		args->floor = (ft_atoi(point + 1) << 16) + 
			(ft_atoi(ft_strchr(point, ',')+ 1) << 8) + 
			ft_atoi(ft_strchr(ft_strchr(point, ',') + 1, ',') + 1);
	}
	else
	{
		args->ceil = (ft_atoi(point + 1) << 16) + 
			(ft_atoi(ft_strchr(point, ',')+ 1) << 8) + 
			ft_atoi(ft_strchr(ft_strchr(point, ',') + 1, ',') + 1);
	}
	ft_parcemap(point, args);
}

int     ft_parcecub(t_args *args, char *arglist)
{
	ft_parceres(args, arglist);
	ft_parcecolor(args, arglist, 'F');
	ft_parcecolor(args, arglist, 'C');
	args->path_no = ft_parcepath(args, arglist, "NO");
	args->path_so = ft_parcepath(args, arglist, "SO");
	args->path_ea = ft_parcepath(args, arglist, "EA");
	args->path_we = ft_parcepath(args, arglist, "WE");
	args->path_s = ft_parcepath(args, arglist, "S");
	return (1);
}
