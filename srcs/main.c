/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 16:33:12 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/13 22:44:36 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		main(int argc, char **argv)
{
	int save;

	save = 0;
	if (argc < 2 || argc == 3 || argc > 4)
	{
		perror("Wrong input params.\n");
		return (1);
	}
	if (argc == 4 && !ft_strnstr(argv[2], "--save", 6)
	{
		perror("If u wanna do a screenshot, use a --save key.\n");
		return (1);
	}
	if (!ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
	{
		perror("Card must be .cub file.");
		return (1);
	}
	if (argc == 4)
		save = 1;
	cub_init(argv, save);
}