# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/13 12:42:52 by axbrisse          #+#    #+#              #
#    Updated: 2022/12/21 05:51:17 by axbrisse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

PATH_SRCS = srcs
PATH_OBJS = objs
PATH_LIBFT = libft
PATH_MLX = minilibx

INCLUDES = -I./includes -I./libft/includes -I./minilibx

MANDATORY += event_handlers
MANDATORY += get_map_dimensions
MANDATORY += initialization
MANDATORY += main

SRCS = ${addsuffix .c, ${MANDATORY}}
OBJS = ${patsubst %.c, ${PATH_OBJS}/%.o, ${SRCS}}
vpath %.c ${PATH_SRCS}

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: ${NAME}

${OBJS}: ${PATH_OBJS}/%.o: %.c
	@mkdir -p ${PATH_OBJS}
	${CC} ${CFLAGS} -c $< -o $@ ${INCLUDES}

${NAME}: ${OBJS}
	${MAKE} -s -C ${PATH_LIBFT} all
	${MAKE} -s -C ${PATH_MLX} all
	${CC} ${CFLAGS} ${OBJS} -L${PATH_LIBFT} -lft -lX11 -lXext -L${PATH_MLX} -lmlx -lm -o ${NAME}

clean:
	${MAKE} -s -C ${PATH_LIBFT} clean
	${MAKE} -s -C ${PATH_MLX} clean
	rm -rf objs

fclean: clean
	${MAKE} -s -C ${PATH_LIBFT} fclean
	rm -f ${NAME}

re: fclean ${NAME}

rebonus: fclean bonus

.PHONY: all clean fclean re
