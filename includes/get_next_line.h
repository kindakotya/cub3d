/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 12:10:19 by gmayweat          #+#    #+#             */
/*   Updated: 2021/04/03 00:05:57 by gmayweat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

int		get_next_line(int fd, char **line);
// size_t	ft_strlen(const char *s);
// char	*ft_strjoin(const char *s1, const char *s2);
// char	*ft_strdup(const char *s);
// void	*ft_calloc(size_t nmemb, size_t size);
void	ft_strnl(char *s);

#endif
