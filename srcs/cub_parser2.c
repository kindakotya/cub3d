/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parser2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 16:44:34 by gmayweat          #+#    #+#             */
/*   Updated: 2021/03/18 17:42:59 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char     *ft_joinread(char *s, char *buf)
{
	char *meow;
	size_t i;
	if (!s)
		meow = ft_strdup(buf);
	else
		meow = ft_strjoin(s, buf);
	if (!meow)
		return (NULL);
	free (s);
	i = 0;
	while (i < 42)
		buf[i++] = '\0';
	return (meow);
}

static char    *ft_readfile(int fd)
{
	char    *s;
	char    buf[42];
	size_t  i;
	int  n;

	i = 0;
	s = NULL;
	while (i < 42)
		buf[i++] = '\0';
	i = 0;
	n = 1;
	while (n > 0)
	{
		n = read(fd, buf, 41);
		if (n == -1)
			return (NULL);
		if (n == 0)
			break ;
		s = ft_joinread(s , buf);
	}
	return (s);
}

int ft_getparam(char *str, t_args *s_args)
{
	int     fd;
	char    *arglist;

	fd = open(str, O_RDONLY);
	if (fd == -1)
		return(-1);
	arglist = ft_readfile(fd);
	close(fd);
	ft_parcecub(s_args, arglist);
	free(arglist);
	return (1);
}

static char		*ft_writex(char *point)
{
	int i;
	char		*mapi;

	i = 0;
	while (point[i] && point[i] != '\n')
		++i;
	mapi = malloc((i + 1) * sizeof(char));
	mapi[i] = '\0';
	while (*point && *point != '\n')
	{
		*mapi = *point;
		++mapi;
		++point;
	}
	return(mapi - i);
}

char	**ft_writemap(char *point)
{
	char **map;
	int i;
	int j;

	j = 0;
	i = 0;
	while (point[j])
		if (point[j++] == '\n')
			++i;
	map = malloc((i + 1) * sizeof(char*));
	map[i] = NULL;
	j = 0;
	while (j < i)
	{
		map[j++] = ft_writex(point);
		while (*point && *point != '\n')
			++point;
		++point;
	}
	return(map);
}