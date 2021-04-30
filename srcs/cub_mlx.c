/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 03:51:29 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/30 01:51:46 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	screen_params(t_mlx *s_mlx, t_args *s_args)
{
	int	screen_size[2];
	int	i;

	i = 0;
	mlx_get_screen_size(s_mlx->mlx, &screen_size[0], &screen_size[1]);
	if (s_args->win_w < 320)
		s_args->win_w = 320;
	if (s_args->win_h < 240)
		s_args->win_h = 240;
	if (s_args->win_w > screen_size[0])
		s_args->win_w = screen_size[0];
	if (s_args->win_h > screen_size[1] - screen_size[1] / 10)
		s_args->win_h = screen_size[1] - screen_size[1] / 10;
	s_args->rays_density = M_PI / 3 / s_args->win_w;
	if (s_args->win_h < s_args->win_w)
		return (s_args->win_h / 5);
	else
		return (s_args->win_w / 5);
}

int	load_texture(void *mlx, t_tex *tex)
{
	tex->img.img = mlx_xpm_file_to_image(mlx, tex->path, &tex->w, &tex->h);
	if (tex->img.img == NULL)
		return (0);
	tex->img.addr = mlx_get_data_addr(tex->img.img,
			&tex->img.bits_per_pixel,
			&tex->img.size_line,
			&tex->img.endian);
	if (tex->img.addr == NULL)
		return (0);
	return (1);
}

void	load_textures(t_mlx *s_mlx, t_args *s_args)
{
	int	i;

	i = 0;
	i = load_texture(s_mlx->mlx, &s_args->tex_no);
	if (i == 0)
		ft_exit(0, s_args, s_mlx, 15);
	i = load_texture(s_mlx->mlx, &s_args->tex_so);
	if (i == 0)
		ft_exit(0, s_args, s_mlx, 16);
	i = load_texture(s_mlx->mlx, &s_args->tex_ea);
	if (i == 0)
		ft_exit(0, s_args, s_mlx, 17);
	i = load_texture(s_mlx->mlx, &s_args->tex_we);
	if (i == 0)
		ft_exit(0, s_args, s_mlx, 18);
	i = load_texture(s_mlx->mlx, &s_args->sprite);
	if (i == 0)
		ft_exit(0, s_args, s_mlx, 19);
}

void	create_images(t_args *s_args, t_mlx *s_mlx)
{
	s_mlx->img.img = mlx_new_image(s_mlx->mlx, s_args->win_w, s_args->win_h);
	if (s_mlx->img.img == NULL)
		ft_exit(0, s_args, s_mlx, 12);
	s_mlx->img.addr = mlx_get_data_addr(s_mlx->img.img,
			&s_mlx->img.bits_per_pixel,
			&s_mlx->img.size_line,
			&s_mlx->img.endian);
	if (s_mlx->img.addr == NULL)
		ft_exit(0, s_args, s_mlx, 13);
	s_mlx->minimap.img = mlx_new_image(s_mlx->mlx,
			s_mlx->m_size, s_mlx->m_size);
	if (s_mlx->minimap.img == NULL)
		ft_exit(0, s_args, s_mlx, 12);
	s_mlx->minimap.addr = mlx_get_data_addr(s_mlx->minimap.img,
			&s_mlx->minimap.bits_per_pixel,
			&s_mlx->minimap.size_line,
			&s_mlx->minimap.endian);
	if (s_mlx->minimap.addr == NULL)
		ft_exit(0, s_args, s_mlx, 13);
}

t_mlx	start_mlx(t_args *s_args)
{
	t_mlx	s_mlx;

	s_mlx.mlx = mlx_init();
	if (s_mlx.mlx == NULL)
		ft_exit(0, s_args, 0, 11);
	s_mlx.m_size = screen_params(s_mlx.mlx, s_args);
	s_mlx.win = mlx_new_window(
			s_mlx.mlx, s_args->win_w, s_args->win_h, "cub3d");
	if (s_mlx.win == NULL)
		ft_exit(0, s_args, &s_mlx, 12);
	create_images(s_args, &s_mlx);
	load_textures(&s_mlx, s_args);
	return (s_mlx);
}
