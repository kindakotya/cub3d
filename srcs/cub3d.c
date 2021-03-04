/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 19:45:54 by gmayweat          #+#    #+#             */
/*   Updated: 2021/02/25 23:01:51 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void     ft_clearstruct(t_args *s_args)
{
    s_args->res_x = 0;
    s_args->res_y = 0;
    s_args->path_no = NULL;
    s_args->path_so = NULL;
    s_args->path_ea = NULL;
    s_args->path_we = NULL;
    s_args->path_s = NULL;
    s_args->floor_r = 0;
    s_args->floor_g = 0;
    s_args->floor_b = 0;
    s_args->ceil_r = 0;
    s_args->ceil_g = 0;
    s_args->ceil_b = 0;
    s_args->map = NULL;
}

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

int             main(int argc, char **argv)
{
    int     fd;
    char    *arglist;
    t_args  s_args;

    ft_clearstruct(&s_args);
    if (argc == 1)
    {
        perror("Gimme card");
        return (-1);
    }
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        return(-1);
    arglist = ft_readfile(fd);
    close(fd);
    ft_parcecub(&s_args, arglist);
    return (0);

}