# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/13 12:42:52 by axbrisse          #+#    #+#              #
#    Updated: 2023/02/05 04:39:13 by axbrisse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := fdf

PATH_SRCS := srcs
PATH_OBJS := objs

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
FILES += main
FILES += utils
FILES += parse_map
FILES += put_lines
FILES += transform

SRCS := ${addsuffix .c, ${FILES}}
OBJS := ${patsubst %.c, ${PATH_OBJS}/%.o, ${SRCS}}
vpath %.c ${PATH_SRCS}

CC := cc
CFLAGS := -Wall -Wextra -Werror

all: ${NAME}

${OBJS}: ${PATH_OBJS}/%.o: %.c ${HEADER}
	@mkdir -p ${PATH_OBJS}
	${CC} ${CFLAGS} -c $< -o $@ ${INCLUDES}

${NAME}: ${LIBFT} ${MLX} ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -L${PATH_LIBFT} -lft -lX11 -lXext -L${PATH_MLX} -lmlx -lm -o ${NAME}

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
	rm -f ${NAME}

re: fclean ${NAME}

.PHONY: all clean fclean re
