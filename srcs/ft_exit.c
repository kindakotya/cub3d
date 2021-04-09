/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 03:34:40 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/09 03:41:40 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_free(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		++i;
	while (i)
		free(arr[--i]);
	free(arr);
}

void		destroy_texture(void *mlx, t_sprite *tex)
{
	free(tex->path);
	mlx_destroy_image(mlx, tex->img.img);
}

void		ft_exit(int fd, t_args *s_args, t_mlx *s_mlx, int return_val)
{
	if (fd)
		close(fd);
	ft_free(s_args->map);
	ft_free(s_args->win);
	destroy_texture(s_mlx->mlx, &s_args->tex_ea);
	destroy_texture(s_mlx->mlx, &s_args->tex_no);
	destroy_texture(s_mlx->mlx, &s_args->sprite);
	destroy_texture(s_mlx->mlx, &s_args->tex_so);
	destroy_texture(s_mlx->mlx, &s_args->tex_we);
	mlx_destroy_image(s_mlx->mlx, s_mlx->img.img);
	mlx_destroy_image(s_mlx->mlx, s_mlx->minimap.img);
	mlx_destroy_window(s_mlx->mlx, s_mlx->win);
	exit(return_val);
}