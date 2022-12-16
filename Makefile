# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/13 12:42:52 by axbrisse          #+#    #+#              #
#    Updated: 2022/12/16 02:57:48 by axbrisse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

PATH_SRCS_M = srcs/mandatory
PATH_SRCS_B = srcs/bonus
PATH_OBJS_M = objs/mandatory
PATH_OBJS_B = objs/bonus
PATH_LIBFT = libft
PATH_MLX = minilibx

INCLUDES = includes

MANDATORY += count_iterations
MANDATORY += event_handlers
MANDATORY += main
MANDATORY += parse_args
MANDATORY += pixels
MANDATORY += scale_coords

BONUS += colors01234
BONUS += colors56789
BONUS += count_iterations
BONUS += event_handlers
BONUS += main
BONUS += parse_args
BONUS += pixels
BONUS += scale_coords

SRCS_M = ${addsuffix .c, ${MANDATORY}}
SRCS_B = ${addsuffix .c, ${BONUS}}
vpath %.c ${PATH_SRCS_B}
vpath %.c ${PATH_SRCS_M}
OBJS_M = ${patsubst %.c, ${PATH_OBJS_M}/%.o, ${SRCS_M}}
OBJS_B = ${patsubst %.c, ${PATH_OBJS_B}/%.o, ${SRCS_B}}

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: ${NAME}

${OBJS_M}: ${PATH_OBJS_M}/%.o: %.c ${HEADER}
	@mkdir -p ${PATH_OBJS_M}
	${CC} ${CFLAGS} -c $< -o $@ -I${INCLUDES}

${NAME}: ${OBJS_M}
	${MAKE} -s -C ${PATH_LIBFT} all
	${MAKE} -s -C ${PATH_MLX} all
	${CC} ${CFLAGS} ${OBJS_M} -L${PATH_LIBFT} -lft -lX11 -lXext -L${PATH_MLX} -lmlx -lm -o ${NAME}

clean:
	${MAKE} -s -C ${PATH_LIBFT} clean
	${MAKE} -s -C ${PATH_MLX} clean
	rm -rf objs

fclean: clean
	${MAKE} -s -C ${PATH_LIBFT} fclean
	rm -f ${NAME}

re: fclean ${NAME}

${OBJS_B}: ${PATH_OBJS_B}/%.o: %.c ${HEADER}
	@mkdir -p ${PATH_OBJS_B}
	${CC} ${CFLAGS} -c $< -o $@ -I${INCLUDES}

bonus: ${OBJS_B}
	${MAKE} -s -C ${PATH_LIBFT} all
	${MAKE} -s -C ${PATH_MLX} all
	${CC} ${CFLAGS} ${OBJS_B} -L${PATH_LIBFT} -lft -lX11 -lXext -L${PATH_MLX} -lmlx -lm -o ${NAME}

rebonus: re bonus

.PHONY: all clean fclean re
