/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 16:17:47 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/22 01:19:17 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parcer_errors(int err_no)
{
	if (err_no == 3)
		perror("Can't open file, friend.\n");
	else if (err_no == 5)
		perror("Can't read from file.\n");
	else if (err_no == 6)
		perror("Map too small.");
	else if (err_no == 7)
		perror("There is no player on map.\n");
	else if (err_no == 8)
		perror("Map is not valid.\n");
	else if (err_no == 9)
		perror("File is not valid.\n");
	// else if (err_no == 10)
}

void	mlx_list(int err_no)
{
	if (err_no == 11)
		perror("Cant init mlx.\n");
	if (err_no == 12)
		perror("Can't create window\n");
	if (err_no == 13)
		perror("Can't create image.\n");
	if (err_no == 14)
		perror("Can't take image addr.\n");
	if (err_no == 15)
		perror("Can't load north texture.\n");
	if (err_no == 16)
		perror("Can't load south texture.\n");
	if (err_no == 17)
		perror("Can't load east texture.\n");
	if (err_no == 18)
		perror("Can't load west texture.\n");
	if (err_no == 19)
		perror("Can't load sprite.\n");
	if (err_no == 20)
		perror("Can't create file.\n");
	if (err_no == 21)
		perror("Can't write to file.\n");
}
int		display_error(int err_no)
{
	if (err_no == 2)
		perror("Malloc error.\n");
	else if (err_no > 2 && err_no <= 10)
		parcer_errors(err_no);
	else if (err_no <= 23)
		mlx_list(err_no);
	// else if (err_no <= 30)
	return (err_no);
}