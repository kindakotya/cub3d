/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 19:45:54 by gmayweat          #+#    #+#             */
/*   Updated: 2021/03/15 19:18:16 by gmayweat         ###   ########.fr       */
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

static int ft_getparam(char *str, t_args *s_args)
{
	int     fd;
	char    *arglist;

	ft_clearstruct(s_args);
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return(-1);
	arglist = ft_readfile(fd);
	close(fd);
	ft_parcecub(s_args, arglist);
	free(arglist);
	return (1);
}

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int             key(int keycode, t_vars *s_vars)
{
	static int x = 0;
	static int y = 0;
	if (keycode == 1 && y < 1080)
		my_mlx_pixel_put(s_vars->img, x, ++y, 0x0000FF00);
	else if (keycode == 0 && x > 0)
		my_mlx_pixel_put(s_vars->img, --x, y, 0x0000FF00);
	else if (keycode == 13 && y > 0)
		my_mlx_pixel_put(s_vars->img, x, --y, 0x0000FF00);
	else if (keycode == 2 && x < 1920)
		my_mlx_pixel_put(s_vars->img, ++x, y, 0x0000FF00);
	else if (keycode == 53)
		exit(0);
	mlx_put_image_to_window(s_vars->mlx, s_vars->win, s_vars->img->img, 0, 0);
	return (1);
}

int             main(int argc, char **argv)
{
	t_args  s_args;
	t_vars s_vars;
	t_data img;
	// int x = 0;
	// int y = 0;
	if (argc == 1)
	{
		perror("Gimme card");
		return (-1);
	}
	ft_getparam(argv[1], &s_args);
	s_vars.mlx = mlx_init();
	s_vars.img = &img;
	s_vars.img->img = mlx_new_image(s_vars.mlx, s_args.res_x, s_args.res_y);
	s_vars.img->addr = mlx_get_data_addr(s_vars.img->img, &s_vars.img->bits_per_pixel,
										&s_vars.img->line_length, &s_vars.img->endian);
	s_vars.win = mlx_new_window(s_vars.mlx, s_args.res_x, s_args.res_y, "meow");
	// while (x < 100)
	// {
	//     y = 0;
	//     while (y < 100)
	//         my_mlx_pixel_put(&s_vars.img, x, y++, 0x00FFF000);
	//     ++x;
	// }


	mlx_hook(s_vars.win, 2, 1L<<0, key, &s_vars);
	mlx_put_image_to_window(s_vars.mlx, s_vars.win, s_vars.img->img, 0, 0);
	mlx_loop(s_vars.mlx);
	return (0);

}