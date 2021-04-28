/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 19:45:54 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/28 23:14:16 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			clear_mlx(t_mlx *s_mlx)
{
	s_mlx->mlx = NULL;
	s_mlx->win = NULL;
	s_mlx->img.img = NULL;
	s_mlx->minimap.img = NULL;
	s_mlx->m_size = 0;
}

static void		clear_sprite(t_tex *sprite)
{
	sprite->h = 0;
	sprite->w = 0;
	sprite->path = NULL;
	sprite->img.img = NULL;
}

static void		clear_args(t_args *s_args)
{
	s_args->win_w = 0;
	s_args->win_h = 0;
	s_args->win = NULL;
	s_args->player.x = 0;
	s_args->player.y = 0;
	s_args->player.aov = 1;
	s_args->screenshot = NULL;
	clear_sprite(&s_args->tex_ea);
	clear_sprite(&s_args->tex_no);
	clear_sprite(&s_args->tex_so);
	clear_sprite(&s_args->tex_we);
	clear_sprite(&s_args->sprite);
	s_args->floor = 0;
	s_args->ceil = 0;
	s_args->map = NULL;
	s_args->map_h = 0;
	s_args->map_w = 0;
}

t_sqr 		fill_sqr(int x, int y, int side, int color)
{
	t_sqr s_sqr;
	s_sqr.x = x;
	s_sqr.y = y;
	s_sqr.side = side;
	s_sqr.color = color;
	return (s_sqr);
}

void	add_floor_ceil(t_img *img, t_args *s_args)
{
	int x;
	int y;

	y = 0;
	while (y < s_args->win_h)
	{
		x = 0;
		while (x < s_args->win_w)
		{	
			if (y < s_args->win_h / 2)
				put_pixel(img, x++, y, s_args->floor);
			else
				put_pixel(img, x++, y, s_args->ceil);
		}
		++y;
	}
}

void		fill_line(t_line *line, t_args *s_args, t_ray *ray, t_tex *tex)
{
	line->y = s_args->win_h / 2 - s_args->win_h /
			(ray->c * cos(ray->fov - s_args->player.aov)) / 2;// * (float)s_args->win_w/(float)s_args->win_h;
	line->length = s_args->win_h /
				(ray->c * cos(ray->fov - s_args->player.aov));
	line->tex = tex;
	line->tex_x = ray->x - floor(ray->x + 0.5);
	line->tex_y = ray->y - floor(ray->y + 0.5);
}

t_ray		set_ray(t_args *s_args)
{
	t_ray ray;

	ray.x = 0;
	ray.y = 0;
	ray.prev_x = 0;
	ray.prev_y = 0;
	ray.player.x = (s_args->player.x);
	ray.player.y = (s_args->player.y);
	ray.fov = s_args->player.aov - 0.52359877559;
	ray.walls = malloc(s_args->win_w * sizeof(double));
	return (ray);
}

int		ray_pos(t_ray *ray, t_args *s_args, int x)
{
	ray->x = ray->player.x + ray->c * cos(ray->fov);
	ray->y = ray->player.y + ray->c * sin(ray->fov);
	if (ray->x < 0 || ray->y < 0 || 
		ray->y >= s_args->map_h || ray->x >= s_args->map_w ||
		s_args->map[(int)ray->y][(int)ray->x] == '1')
		{
			ray->walls[x] = ray->c;
			return (1);
		}
	return (0);
}

void	drawing_params(t_args *s_args, t_mlx *s_mlx, t_ray *ray, t_line *line)
{
	if (fabs(ray->prev_x - ray->x) > fabs(ray->prev_y - ray->y))// - ray->y < ray->prev_x - ray->x)
		{
			if (ray->player.y < ray->y)
				fill_line(line, s_args, ray, &s_args->tex_no);
			else
				fill_line(line, s_args, ray, &s_args->tex_so);
		}
	else
		{
			if (ray->player.x < ray->x)
				fill_line(line, s_args, ray, &s_args->tex_we);
			else 
				fill_line(line, s_args, ray, &s_args->tex_ea);
		}
	if (fabs(line->tex_x) < fabs(line->tex_y))
		draw_line(s_args, line, s_mlx, line->tex_y * line->tex->w);
	else
		draw_line(s_args, line, s_mlx, line->tex_x * line->tex->w);
	ray->prev_x = ray->x;
	ray->prev_y = ray->y;
}

void	push_mid(t_sprite *sprites, t_sprite *sprite)
{
	t_sprite *meow;

	meow = sprites;
	while (meow && sprite->dist <= meow->dist)
		meow = meow->next;
	while (sprites->next && sprites->next != meow)
		sprites = sprites->next;
	sprites->next = sprite;
	sprite->next = meow;
}

void	add_sprite(t_sprite **sprites, t_sprite *sprite)
{
	if (*sprites == NULL)
	{
		*sprites = sprite;
		return ;
	}
	if (sprite->dist > (*sprites)->dist)
	{
		sprite->next = *sprites;
		*sprites = sprite;
		return ;
	}
	push_mid(*sprites, sprite);
}

t_sprite	*create_sprite()
{
	t_sprite *sprites;

	sprites = malloc(sizeof(t_sprite));
	if (sprites == NULL)
		return (NULL);
	sprites->next = NULL;
	sprites->tex_x = 0;
	return (sprites);
}

void	free_sprites(t_sprite *sprites)
{
	t_sprite *prev_sprite;

	if (sprites)
	{
		while (sprites->next)
		{
			prev_sprite = sprites;
			sprites = sprites->next;
			free(prev_sprite);
		}
		free(sprites);
	}
}

int	check_sprite(t_ray *ray, t_sprite *sprites, double *x, double *y)
{
	*y = floor(ray->y) + 0.5;
	*x = floor(ray->x) + 0.5;
	if (!sprites)
		return (1);
	while (sprites)
	{
		if (fabs((sprites)->y - *y) < 0.1
			&& fabs((sprites)->x - *x) < 0.1)
			return (0);
		sprites = sprites->next;
	}
	return (1);
}

int	find_sprite(t_ray *ray, t_args *s_args, t_sprite **sprites)
{
	t_sprite *sprite;
	double x;
	double y;

	if (s_args->map[(int)ray->y][(int)ray->x] == '2'
	&& check_sprite(ray, *sprites, &x, &y))
	{
		sprite = create_sprite();
		if (sprite == NULL)
		{
			free_sprites(*sprites);
			return (0);
		}
		sprite->x = x;
		sprite->y = y;
		sprite->dist = sqrt(pow(s_args->player.x - sprite->x, 2) +
		pow(s_args->player.y - sprite->y, 2));
		sprite->size = s_args->win_h / sprite->dist;
		sprite->dir = atan2(sprite->y - s_args->player.y, sprite->x - s_args->player.x);
		while (sprite->dir - s_args->player.aov > M_PI) sprite->dir -= 6.28318530718;
		while (sprite->dir - s_args->player.aov < -M_PI) sprite->dir += 6.28318530718;
		sprite->w = (sprite->dir - s_args->player.aov)/1.0471975512*s_args->win_w + s_args->win_w/2 - sprite->size / 2;
		sprite->h = s_args->win_h / 2 - sprite->size / 2;
		add_sprite(sprites, sprite);
		(*sprites)->tex_x++;
	}
	return (1);
}

void	draw_sprites(t_args *s_args, t_mlx *s_mlx, t_sprite *sprites, t_ray *ray)
{
	int i;
	unsigned int color;
	int j;

	if (sprites == NULL)
		return ;
	while (sprites)
	{
		i = 0;
		while (i < sprites->size)
		{
			j = 0;
			if (sprites->h + i < s_args->win_h)
			{
			while (j < sprites->size)
			{
				if (sprites->w + j < s_args->win_w && sprites->dist < ray->walls[sprites->w + j])// / s_args->side)
				{
					color = take_color(&s_args->sprite.img, j * s_args->sprite.w / sprites->size, i * s_args->sprite.h / sprites->size);
					if (color >> 24 == 0)
						put_pixel(&s_mlx->img, sprites->w + j, sprites->h + i, color);
				}
				++j;
			}
			}
			++i;
		}
		sprites = sprites->next;
	}
}

void			raycast(t_args *s_args, t_mlx *s_mlx)
{
	t_ray ray;
	t_line line;
	t_sprite *sprites;

	sprites = NULL;
	add_floor_ceil(&s_mlx->img, s_args);
	ray = set_ray(s_args);
	line.x = 0;
	while (line.x < s_args->win_w)
	{
		ray.c = 0.1;
		while (!ray_pos(&ray, s_args, line.x))
		{
			if (ray.c < 1)
				ray.c += 0.011;
			else
				ray.c = pow(ray.c, 1.5);
			if (!find_sprite(&ray, s_args, &sprites))
				ft_exit(0, s_args, s_mlx, 2);
		}
		drawing_params(s_args, s_mlx, &ray, &line);
		++line.x;
		ray.fov += s_args->rays_density;
	}
	draw_sprites(s_args, s_mlx, sprites, &ray);
	mlx_put_image_to_window(s_mlx->mlx, s_mlx->win, s_mlx->img.img, 0, 0);
	free(ray.walls);
	free_sprites(sprites);
}

int			red_cross(t_all *s_all)
{
	ft_exit(0, s_all->s_args, s_all->s_mlx, 0);
	return (0);
}

int				cub_init(char **input, int save)
{
	t_all s_all;
	t_args s_args;
	t_mlx s_mlx;

	clear_args(&s_args);
	getparam(input[1], &s_args);
	if (save)
		s_args.screenshot = input[3];
	s_mlx = start_mlx(&s_args);
	s_all.s_args = &s_args;
	s_all.s_mlx = &s_mlx;
	raycast(&s_args, &s_mlx);
	draw_minimap(&s_args, &s_mlx);
	mlx_put_image_to_window(s_mlx.mlx, s_mlx.win, s_mlx.img.img, 0, 0);
	mlx_hook(s_mlx.win, 2, 1, &key_pressed, &s_all);
	mlx_hook(s_mlx.win, 17, 0, &red_cross, &s_all);
	mlx_loop(s_mlx.mlx);

	return (0);
}