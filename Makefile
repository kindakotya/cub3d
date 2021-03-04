# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/25 22:40:29 by gmayweat          #+#    #+#              #
#    Updated: 2021/02/25 23:13:59 by gmayweat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

LIBFT = libft/libft.a

SRCS =					cub3d.c\
						cub_parser.c

HEAD = cub3d.h

OBJS = $(SRCS:.c=.o)

OBJDIR = objs

OBJSPATH = $(addprefix objs/, $(OBJS))

vpath %.o objs
vpath %.c srcs
vpath %.h includes

.Phony: all $(NAME) clean fclean re libft.a $(OBJDIR)

all: libft.a $(NAME)

libft.a:
	$(MAKE) -C libft

$(NAME): $(LIBFT) $(OBJDIR) $(OBJS)
	cp $(LIBFT) $(NAME)
	gcc -g -Wall -Wextra -Werror -o $(NAME) $(OBJSPATH) libft/libft.a

%.o : %.c $(HEAD)
	gcc -g -Wall -Wextra -Werror -Iincludes -o $(patsubst srcs/%, objs/%, $(patsubst %.c, %.o, $<)) -c $<

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	$(MAKE) -C libft clean
	rm -rf $(OBJDIR)

fclean:
	$(MAKE) -C libft fclean
	rm -rf $(OBJDIR) $(NAME)

re: fclean all