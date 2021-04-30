/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 16:33:12 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/29 17:46:46 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	if (argc < 2 || argc > 4)
	{
		write(1, "Error: Wrong input params.\n", 28);
		return (1);
	}
	if (argc > 2 && !ft_strnstr(argv[2], "--save", ft_strlen(argv[2])))
	{
		write(1, "Error: If u wanna do a screenshot, use a --save key.\n", 54);
		return (1);
	}
	if (!ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
	{
		write(1, "Error: Card must be .cub file.\n", 32);
		return (1);
	}
	if (argc == 4)
		cub_init(argv, 2);
	else if (argc == 3)
		cub_init(argv, 1);
	else
		cub_init(argv, 0);
	return (0);
}
