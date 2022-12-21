/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 04:42:40 by axbrisse          #+#    #+#             */
/*   Updated: 2022/12/21 03:55:45 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"

# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/types.h>

# define WINDOW_WIDTH 960
# define WINDOW_HEIGHT 540

# define DEFAULT_COLOR 0xffffff

enum {
	ON_KEY_DOWN = 2,
	ON_DESTROY = 17
};

enum {
	NO_EVENT_MASK = 0,
	KEY_PRESS_MASK = 1,
};

enum {
	ESC = 65307,
};

typedef struct s_map {
	int				**zs;
	int				**colors;
	unsigned int	height;
	unsigned int	width;
}	t_map;

typedef struct s_data {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		endian;
	int		line_length;
	t_map	map;
}	t_data;

#endif