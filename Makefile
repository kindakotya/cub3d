# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/25 22:40:29 by gmayweat          #+#    #+#              #
#    Updated: 2021/04/28 21:55:07 by gmayweat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

LIBFT = libft/libft.a

SRCS =					cub3d.c\
						cub_keyhooks.c\
						cub_parser.c\
						params_parcer.c\
						parcer_utils.c\
						player_parcer.c\
						map_parcer.c\
						ft_exit.c\
						drawings.c\
						minimap.c\
						screenshot.c\
						cub_errors.c\
						cub_mlx.c\
						gnl/get_next_line.c\
						gnl/get_next_line_utils.c\
						main.c

HEAD = cub3d.h

OBJS = $(SRCS:.c=.o)

OBJDIR = objs

OBJSPATH = $(patsubst objs/gnl%, gnl%, $(addprefix objs/, $(OBJS)))

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
	rm -rf meow.bmp
	clang -g -O3 -Iincludes -Ilibft -framework OpenGL -framework AppKit -Wall -Wextra -Werror\
		-o $(NAME) $(OBJSPATH) libft/libft.a libmlx.dylib

%.o : %.c $(HEAD)
	clang -g -Wall -Wextra -Werror -Ilibft -Iincludes -o $(patsubst srcs/%, objs/%, $(patsubst %.c, %.o, $<)) -c $<

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	$(MAKE) -C libft clean
	$(MAKE) -C mlx clean
	rm -rf $(OBJDIR)

fclean:
	$(MAKE) -C libft fclean
	$(MAKE) -C mlx clean
	rm -rf $(OBJSPATH) $(NAME) libmlx.dylib

re: fclean all
