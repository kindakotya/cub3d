# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/25 22:40:29 by gmayweat          #+#    #+#              #
#    Updated: 2021/03/11 20:32:33 by gmayweat         ###   ########.fr        #
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

.Phony: all $(NAME) clean fclean re libft.a libmlx.dylib $(OBJDIR)

all: libft.a libmlx.dylib $(NAME)

libft.a:
	$(MAKE) -C libft

libmlx.dylib:
	$(MAKE) -C mlx
	cp mlx/libmlx.dylib .

$(NAME): $(LIBFT) libmlx.dylib $(OBJDIR) $(OBJS)
	clang -g -Iincludes -framework OpenGL -framework AppKit -Wall -Wextra -Werror\
		-o $(NAME) $(OBJSPATH) libft/libft.a libmlx.dylib

%.o : %.c $(HEAD)
	clang -g -Wall -Wextra -Werror -Iincludes -o $(patsubst srcs/%, objs/%, $(patsubst %.c, %.o, $<)) -c $<

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	$(MAKE) -C libft clean
	$(MAKE) -C mlx clean
	rm -rf $(OBJDIR)

fclean:
	$(MAKE) -C libft fclean
	$(MAKE) -C mlx clean
	rm -rf $(OBJDIR) $(NAME)

re: fclean all