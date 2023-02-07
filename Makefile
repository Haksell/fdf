# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/13 12:42:52 by axbrisse          #+#    #+#              #
#    Updated: 2023/02/07 11:05:34 by axbrisse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := fdf
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

FILES += create_vertices
FILES += event_handlers
FILES += get_map_dimensions
FILES += image
FILES += initialization
FILES += utils
FILES += parse_map
FILES += projections
FILES += rotations
FILES += put_lines
FILES += transform

vpath %.c ${PATH_SRCS}
ifeq (test, ${findstring test, ${MAKECMDGOALS}})
	vpath %.c ${PATH_TESTS}
	FILES += test_parse_map
else
	FILES += main
endif

SRCS := ${addsuffix .c, ${FILES}}
OBJS := ${patsubst %.c, ${PATH_OBJS}/%.o, ${SRCS}}

CC := cc -Wall -Wextra -Werror

all: ${NAME}

${OBJS}: ${PATH_OBJS}/%.o: %.c ${HEADER}
	@mkdir -p ${PATH_OBJS}
	${CC} -c $< -o $@ ${INCLUDES}

${NAME}: ${LIBFT} ${MLX} ${OBJS}
	${CC} ${OBJS} -L${PATH_LIBFT} -lft -lX11 -lXext -L${PATH_MLX} -lmlx -lm -o ${NAME}

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
	rm -f ${NAME} ${TEST}

re: fclean ${NAME}

test: ${LIBFT} ${MLX} ${OBJS}
	@${CC} ${OBJS} -L${PATH_LIBFT} -lft -lX11 -lXext -L${PATH_MLX} -lmlx -lm -o ${TEST}
	@./${TEST} 2> /dev/null

retest: fclean test

norm:
	norminette includes libft srcs tests

.PHONY: all clean fclean re test retest norm
