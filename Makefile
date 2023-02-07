# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/13 12:42:52 by axbrisse          #+#    #+#              #
#    Updated: 2023/02/07 16:16:30 by axbrisse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := fdf
BONUS := fdf_bonus
TEST := test

PATH_SRCS := srcs
PATH_OBJS := objs
PATH_TESTS := tests

PATH_LIBFT := libft
PATH_MLX := mlx
LIBFT := libft/libft.a
MLX := mlx/libmlx.a

INCLUDES := -I./includes -I./${PATH_LIBFT}/includes -I./${PATH_MLX}
HEADER := includes/fdf.h

FILES += bresenham pixels put_lines render_frame
FILES += handle_key_down handle_mouse
FILES += parse_cell parse_map
FILES += cabinet isometric parallel
FILES += linear_transformations transform_vertex
FILES += clean initialize math

vpath %.c ${PATH_SRCS}/display
vpath %.c ${PATH_SRCS}/events
vpath %.c ${PATH_SRCS}/parsing
vpath %.c ${PATH_SRCS}/projections
vpath %.c ${PATH_SRCS}/transform
vpath %.c ${PATH_SRCS}/utils

ifeq (test, ${findstring test, ${MAKECMDGOALS}})
	vpath %.c ${PATH_TESTS}
	FILES += test_parse_map
else
	vpath %.c ${PATH_SRCS}
	FILES += main
endif

SRCS := ${addsuffix .c, ${FILES}}
OBJS := ${patsubst %.c, ${PATH_OBJS}/%.o, ${SRCS}}

CC := cc -Wall -Wextra -Werror

all: ${NAME}

${OBJS}: ${PATH_OBJS}/%.o: %.c ${HEADER}
	@mkdir -p ${PATH_OBJS}
	${CC} -c $< -o $@ ${INCLUDES}

${BONUS} ${NAME}: ${LIBFT} ${MLX} ${OBJS}
	${CC} ${OBJS} -L${PATH_LIBFT} -lft -lX11 -lXext -L${PATH_MLX} -lmlx -lm -o $@

${LIBFT}:
	${MAKE} -s -C ${PATH_LIBFT} all

${MLX}:
	${MAKE} -s -C ${PATH_MLX} all

clean:
	${MAKE} -s -C ${PATH_LIBFT} clean
	${MAKE} -s -C ${PATH_MLX} clean
	rm -rf objs

fclean: clean
	${MAKE} -s -C ${PATH_LIBFT} fclean
	rm -f ${BONUS} ${NAME} ${TEST}

re: fclean ${NAME}

test: ${LIBFT} ${MLX} ${OBJS}
	@${CC} ${OBJS} -L${PATH_LIBFT} -lft -lX11 -lXext -L${PATH_MLX} -lmlx -lm -o ${TEST}
	@./${TEST} 2> /dev/null

retest: fclean test

norm:
	norminette includes libft srcs tests

bonus: ${BONUS}

.PHONY: all bonus clean fclean norm re retest test
