/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 00:25:36 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/09 03:52:16 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_valid_char(int c)
{
	if (c == '0' || c == '1' || c == '2' || is_side_of_world(c))
		return (1);
	return (0);
}

int		is_side_of_world(int c)
{
	if (c == 'N' || c == 'W' || c == 'S' || c == 'E')
		return (1);
	return (0);
}

void	skip_spaces(char **s)
{
	while (**s && **s == ' ')
		++(*s);
}

void	skip_numbers(char **s)
{
	while (**s && ft_isalnum(**s))
		++(*s);
}

char	**add_string(char **arr1, char *str)
{
	char	**arr2;
	int		i;

	i = 0;
	while (arr1[i])
		++i;
	arr2 = malloc((i + 2) * sizeof(char*));
	if (arr2 == NULL)
	{
		perror("Malloc error.\n");
		return(NULL);
	}
	i = 0;
	while (arr1[i])
	{
		arr2[i] = arr1[i];
		++i;
	}
	arr2[i] = str;
	arr2[i + 1] = NULL;
	free(arr1);
	return (arr2);
}