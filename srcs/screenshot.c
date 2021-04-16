/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 17:08:52 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/15 17:41:21 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int		write_header(int fd, t_args *s_args)
// {
// 	int i;
// 	unsigned char header[54];

// 	i = 0;
// 	while (i < 54)
// 		header[i++] = '\0';
	
// }

void	screenshot(t_args *s_args, t_mlx *s_mlx)
{
	int fd;

	fd = 0;
	fd = open(s_args->screenshot, O_CREAT | O_WRONLY | O_TRUNC | O_APPEND);
	if (fd == -1)
		ft_exit(0, s_args, s_mlx, 20);
	close(fd);
}