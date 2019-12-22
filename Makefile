# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sjamie <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/12 19:57:44 by sjamie            #+#    #+#              #
#    Updated: 2019/11/12 19:57:45 by sjamie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= lemin

CC				= gcc  -Wall -Werror -Wextra
HEADER			= includes/
CFLAGS			= -I $(HEADER)

SRC				= src/main.c \
				  src/reader/setup.c \
				  src/reader/rooms.c \
				  src/reader/links.c \
				  src/reader/tmp.c \
				  src/reader/die_atoi.c \
				  src/dijkstra/dijkstra.c \
				  src/dijkstra/result.c \
				  src/dijkstra/helps.c \
				  src/dijkstra/split.c \
				  src/suurballe/suurballe.c \
				  src/suurballe/suurballe1.c \
				  src/suurballe/cp_paths.c \
				  src/way/search_ways.c \
				  src/way/ants_going.c \
				  src/free.c \
				  src/way/helps.c \
				  gnl/get_next_line.c

OBJ = $(patsubst %.c,%.o,$(SRC))

all: $(NAME)

$(NAME): lib $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) dgraph/dgraph.a -L gnl/libft/ -lft  -framework OpenGL -framework AppKit

lib:
	make -C gnl/libft

clean:
	/bin/rm -f $(OBJ)
	make -C gnl/libft clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C gnl/libft fclean

re: fclean all

.PHONY: clean fclean all re
