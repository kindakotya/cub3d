/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 00:46:57 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/30 17:40:10 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	*set_ray(t_ray *ray, t_args *s_args)
{
	ray->x = 0;
	ray->y = 0;
	ray->prev_x[0] = 0;
	ray->prev_y[0] = 0;
	ray->prev_x[1] = 0;
	ray->prev_y[1] = 0;
	ray->fov = s_args->player.aov - 0.52359877559;
	ray->walls = malloc(s_args->win_w * sizeof(double));
	return (ray->walls);
}

static int	ray_pos(t_ray *ray, t_args *s_args)
{
	ray->x = s_args->player.x + ray->c * cos(ray->fov);
	ray->y = s_args->player.y + ray->c * sin(ray->fov);
	if (ray->x < 0 || ray->y < 0
		|| ray->y >= s_args->map_h || ray->x >= s_args->map_w
		|| s_args->map[(int)ray->y][(int)ray->x] == '1')
	{
		return (1);
	}
	return (0);
}

static void	one_line(t_all *s_all, t_ray *ray, t_line *line, t_sprite **sprites)
{
	ray->c = 0.1;
	while (1)
	{
		if (!ray_pos(ray, s_all->s_args))
		{
			ray->c *= 1.0015;
			if (find_sprite(ray, s_all->s_args, sprites) == 0)
				ft_exit(0, s_all->s_args, s_all->s_mlx, 2);
		}
		else
		{
			while (ray_pos(ray, s_all->s_args))
				ray->c -= 0.0001;
			ray->c += 0.0001;
			ray->walls[line->x] = ray->c;
			break ;
		}
	}
	drawing_params(s_all->s_args, s_all->s_mlx, ray, line);
	++line->x;
	ray->fov += s_all->s_args->rays_density;
}

void	raycast(t_all *s_all)
{
	t_ray		ray;
	t_line		line;
	t_sprite	*sprites;

	sprites = NULL;
	draw_floor_ceil(&s_all->s_mlx->img, s_all->s_args);
	if (set_ray(&ray, s_all->s_args) == NULL)
		ft_exit(0, s_all->s_args, s_all->s_mlx, 2);
	line.x = 0;
	while (line.x < s_all->s_args->win_w)
		one_line(s_all, &ray, &line, &sprites);
	draw_sprites(s_all, sprites, &ray);
	mlx_put_image_to_window(s_all->s_mlx->mlx, s_all->s_mlx->win,
		s_all->s_mlx->img.img, 0, 0);
	free(ray.walls);
	free_sprites(sprites);
}
