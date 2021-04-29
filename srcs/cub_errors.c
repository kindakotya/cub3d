/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 16:17:47 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/29 03:24:54 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	parcer_list1(int err_no)
{
	if (err_no == 3)
		write(1, "Error: Can't open file, friend.\n", 33);
	else if (err_no == 5)
		write(1, "Error: Can't read from file.\n", 30);
	else if (err_no == 6)
		write(1, "Error: Map too small.\n", 23);
	else if (err_no == 7)
		write(1, "Error: There is no player on map.\n", 35);
	else if (err_no == 8)
		write(1, "Error: Map is not valid.\n", 26);
	else if (err_no == 9)
		write(1, "Error: File is not valid.\n", 27);
}

static void	parcer_list2(int err_no)
{
	if (err_no == 24)
		write(1, "Error: Resolution is wrong.\n", 29);
	if (err_no == 25)
		write(1, "Error: Path to the north texture is wrong.\n", 44);
	if (err_no == 26)
		write(1, "Error: Path to the south texture is wrong.\n", 44);
	if (err_no == 27)
		write(1, "Error: Path to the east texture is wrong.\n", 43);
	if (err_no == 28)
		write(1, "Error: Path to the west texture is wrong.\n", 43);
	if (err_no == 29)
		write(1, "Error: Path to the sprite is wrong.\n", 37);
	if (err_no == 30)
		write(1, "Error: Floor color is wrong.\n", 30);
	if (err_no == 31)
		write(1, "Error: Ceil color is wrong.\n", 29);
}

static void	mlx_list(int err_no)
{
	if (err_no == 11)
		write(1, "Error: Cant init mlx.\n", 23);
	if (err_no == 12)
		write(1, "Error: Can't create window\n", 28);
	if (err_no == 13)
		write(1, "Error: Can't create image.\n", 28);
	if (err_no == 14)
		write(1, "Error: Can't take image addr.\n", 31);
	if (err_no == 15)
		write(1, "Error: Can't load north texture.\n", 34);
	if (err_no == 16)
		write(1, "Error: Can't load south texture.\n", 34);
	if (err_no == 17)
		write(1, "Error: Can't load east texture.\n", 33);
	if (err_no == 18)
		write(1, "Error: Can't load west texture.\n", 33);
	if (err_no == 19)
		write(1, "Error: Can't load sprite.\n", 27);
	if (err_no == 20)
		write(1, "Error: Can't create file.\n", 27);
	if (err_no == 21)
		write(1, "Error: Can't write to file.\n", 29);
}

int	display_error(int err_no)
{
	if (err_no == 2)
		write(1, "Malloc error.\n", 15);
	else if (err_no <= 10)
		parcer_list1(err_no);
	else if (err_no <= 23)
		mlx_list(err_no);
	else if (err_no <= 35)
		parcer_list2(err_no);
	return (err_no);
}
