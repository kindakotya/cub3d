/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 16:33:12 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/10 02:50:29 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		main(int argc, char **argv)
{
	if (argc != 2)
	{
		perror("Gimme card.");
		return (1);
	}
	if (!ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
	{
		perror("Card must be .cub file.");
		return (2);
	}
	cub_init(argv[1]);
}