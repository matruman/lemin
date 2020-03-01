# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sjamie <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/12 19:57:44 by sjamie            #+#    #+#              #
#    Updated: 2020/01/26 16:37:05 by matruman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= lem-in

CC				= gcc
HEADER			= includes/
CFLAGS			= -Wall -Werror -Wextra -I $(HEADER)

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
				  src/way/helps.c \
				  src/way/sorting.c \
				  src/way/lm_itoa.c \
				  src/way/calc.c \
				  src/free.c \
				  src/reader/output.c \
				  gnl/get_next_line.c

LIB = gnl/libft/libft.a
OBJ = $(patsubst %.c,%.o,$(SRC))

all: lib $(NAME)

$(NAME): $(OBJ) $(LIB)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) -L gnl/libft -lft

$(LIB):

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
