/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 19:45:54 by gmayweat          #+#    #+#             */
/*   Updated: 2021/03/18 17:45:10 by gmayweat         ###   ########.fr       */
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
	s_args->floor = 0;
	s_args->ceil = 0;
	s_args->map = NULL;
}

void            my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char    *dst;

    dst = img->addr + (y * img->size_line + x * (img->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

static int print_2dmap(t_args s_args, t_mlx s_mlx)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (s_args.)
}

int             cub_init(char *input)
{
	t_args s_args;
	t_mlx s_mlx;
	t_img img;
	// int x = 0;
	// int y = 0;

	ft_clearstruct(&s_args);
	ft_getparam(input, &s_args);
	s_mlx.img = &img;
	mlx_init(s_mlx.mlx);
	mlx_new_image(s_mlx.mlx, s_args.res_x, s_args.res_y);
	mlx_get_data_addr(s_mlx.img->img, &s_mlx.img->bits_per_pixel,
						&s_mlx.img->size_line, &s_mlx.img->endian);
	return (0);
}