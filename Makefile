# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/13 12:42:52 by axbrisse          #+#    #+#              #
#    Updated: 2022/12/15 20:59:06 by axbrisse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

PATH_SRCS = srcs
PATH_OBJS = objs
PATH_LIBFT = libft
PATH_MLX = minilibx

FILES += count_iterations
FILES += event_handlers
FILES += main
FILES += parse_args
FILES += pixels
FILES += scale_coords

SRCS = ${addsuffix .c, ${FILES}}
vpath %.c ${PATH_SRCS}
OBJS = ${patsubst %.c, ${PATH_OBJS}/%.o, ${SRCS}}

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: ${NAME}

${OBJS}: ${PATH_OBJS}/%.o: %.c ${HEADER}
	@mkdir -p ${PATH_OBJS}
	${CC} ${CFLAGS} -c $< -o $@ -I./includes

${NAME}: ${OBJS}
	${MAKE} -s -C ${PATH_LIBFT} all
	${MAKE} -s -C ${PATH_MLX} all
	${CC} ${CFLAGS} ${OBJS} -L${PATH_LIBFT} -lft -lX11 -lXext -L${PATH_MLX} -lmlx -lm -o ${NAME}

clean:
	${MAKE} -s -C ${PATH_LIBFT} clean
	${MAKE} -s -C ${PATH_MLX} clean
	rm -rf ${PATH_OBJS}

fclean: clean
	${MAKE} -s -C ${PATH_LIBFT} fclean
	rm -f ${NAME}

re: fclean ${NAME}

.PHONY: all clean fclean re
