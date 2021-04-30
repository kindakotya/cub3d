# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmayweat <gmayweat@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/25 22:40:29 by gmayweat          #+#    #+#              #
#    Updated: 2021/04/30 17:40:52 by gmayweat         ###   ########.fr        #
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
						sprites_utils.c\
						struct_clear.c\
						draw_utils.c\
						raycast.c\
						sprites.c\
						gnl/get_next_line.c\
						gnl/get_next_line_utils.c\
						main.c

HEAD = cub3d.h

OBJS = $(SRCS:.c=.o)

OBJDIR = objs

OBJSPATH = $(patsubst objs/gnl%, gnl%, $(addprefix objs/, $(OBJS)))

FLAGS = -O3 -Wall -Wextra -Werror -Imlx -Ilibft -Iincludes

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
	clang $(FLAGS) -framework OpenGL -framework AppKit\
		-o $(NAME) $(OBJSPATH) libft/libft.a libmlx.dylib

%.o : %.c $(HEAD)
	clang $(FLAGS) -o $(patsubst srcs/%, objs/%, $(patsubst %.c, %.o, $<)) -c $<

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	$(MAKE) -C libft clean
	$(MAKE) -C mlx clean
	rm -rf $(OBJDIR) $(OBJSPATH) libmlx.dylib

fclean:
	$(MAKE) -C libft fclean
	$(MAKE) -C mlx clean
	rm -rf $(OBJDIR) $(OBJSPATH) $(NAME) libmlx.dylib

re: fclean all
