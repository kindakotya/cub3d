/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 22:18:56 by gmayweat          #+#    #+#             */
/*   Updated: 2021/02/22 22:30:25 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void    *ft_realloc(char *s, size_t size)
{
    char    *meow;
    size_t  i;

    meow = malloc(size);
    if (!meow)
        return (NULL);
    while (s[i])
    {
        meow[i] = s[i];
        ++i;
    }
    free(s);
    return (meow);
}