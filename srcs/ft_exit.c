/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 03:34:40 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/10 02:41:06 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		ft_free(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		++i;
	while (i)
		free(arr[--i]);
	free(arr);
}

static void		destroy_textures(void *mlx, t_args *s_args)
{
	if (s_args->tex_no.path)
		free(s_args->tex_no.path);
	if (s_args->tex_no.img.img)
		mlx_destroy_image(mlx, s_args->tex_no.img.img);
	if (s_args->tex_so.path)
		free(s_args->tex_so.path);
	if (s_args->tex_so.img.img)
		mlx_destroy_image(mlx, s_args->tex_so.img.img);
	if (s_args->tex_ea.path)
		free(s_args->tex_ea.path);
	if (s_args->tex_ea.img.img)
		mlx_destroy_image(mlx, s_args->tex_ea.img.img);
	if (s_args->tex_we.path)
		free(s_args->tex_we.path);
	if (s_args->tex_we.img.img)
		mlx_destroy_image(mlx, s_args->tex_we.img.img);
	if (s_args->sprite.path)
		free(s_args->sprite.path);
	if (s_args->sprite.img.img)
		mlx_destroy_image(mlx, s_args->sprite.img.img);
}

static void		end_mlx(t_mlx *s_mlx)
{
	if (s_mlx->win)
		mlx_destroy_window(s_mlx->mlx, s_mlx->win);
	if (s_mlx->img.img)
		mlx_destroy_image(s_mlx->mlx, s_mlx->img.img);
	if (s_mlx->minimap.img)
		mlx_destroy_image(s_mlx->mlx, s_mlx->minimap.img);
}

void		ft_exit(int fd, t_args *s_args, t_mlx *s_mlx, int return_val)
{
	if (fd)
		close(fd);
	if (s_args->map)
		ft_free(s_args->map);
	if (s_args->win)
		ft_free(s_args->win);
	if (s_mlx)
	{
		if (s_mlx->mlx)
			destroy_textures(s_mlx->mlx, s_args);
		end_mlx(s_mlx);
	}
	//getchar();
	exit(return_val);
}