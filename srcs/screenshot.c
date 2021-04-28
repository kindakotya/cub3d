/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 17:08:52 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/28 19:59:51 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	write_four_bites(unsigned char *point, int value)
{
	point[0] = (unsigned char)(value);
	point[1] = (unsigned char)(value >> 8);
	point[2] = (unsigned char)(value >> 16);
	point[3] = (unsigned char)(value >> 24);
}

int	write_header(int fd, t_args *s_args)
{
	int				i;
	int				size;
	unsigned char	header[54];

	i = 0;
	while (i < 54)
		header[i++] = '\0';
	header[0] = 'B';
	header[1] = 'M';
	size = 54 + (3 * (s_args->win_w)) * s_args->win_h;
	write_four_bites(header + 2, size);
	header[10] = 54;
	header[14] = 40;
	write_four_bites(header + 18, s_args->win_w);
	write_four_bites(header + 22, s_args->win_h);
	header[26] = 1;
	header[28] = 24;
	return (write(fd, header, 54));
}

static void	write_array(int fd, t_args *s_args, t_mlx *s_mlx)
{
	int				y;
	int				x;
	unsigned int	color;

	y = s_args->win_h - 1;
	while (y >= 0)
	{
		x = s_args->win_w - 1;
		while (x >= 0)
		{
			color = take_color(&s_mlx->img, x, y);
			if (write(fd, &color, 3) < 0)
				ft_exit(fd, s_args, s_mlx, 21);
			--x;
		}
		--y;
	}
}

void	screenshot(t_args *s_args, t_mlx *s_mlx)
{
	int	fd;

	if (!*s_args->screenshot)
	{
		perror("You did screenshot earlier.\n");
		return ;
	}
	fd = 0;
	fd = open(s_args->screenshot, O_CREAT | O_WRONLY | O_TRUNC | O_APPEND);
	if (fd == -1)
		ft_exit(0, s_args, s_mlx, 20);
	if (write_header(fd, s_args) < 0)
		ft_exit(fd, s_args, s_mlx, 21);
	write_array(fd, s_args, s_mlx);
	close(fd);
	s_args->screenshot = "\0";
}
