/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parser2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 16:44:34 by gmayweat          #+#    #+#             */
/*   Updated: 2021/03/20 21:54:24 by gmayweat         ###   ########.fr       */
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
