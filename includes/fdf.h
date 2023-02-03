/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 04:42:40 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/03 02:43:37 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"

# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/types.h>

# include <stdio.h> // TODO

# ifndef M_PI
#  define M_PI 3.141592653589793
# endif
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 800
# define WHITE 0xffffff
# define BLACK 0x000000
# define DEFAULT_Z_FACTOR 42.0 // TODO compute optimal
# define TRANSLATION 10.0
# define SPACES " \t\n\v\f\r"

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
	KEY_LEFT = 65361,
	KEY_UP = 65362,
	KEY_RIGHT = 65363,
	KEY_DOWN = 65364,
};

typedef struct s_map {
	double	**zs;
	int		**colors;
	int		height;
	int		width;
}	t_map;

typedef struct s_params {
	double	z_factor;
	double	zoom;
	double	tx;
	double	ty;
	double	rx;
	double	ry;
	double	rz;
}	t_params;

typedef struct s_data {
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			endian;
	int			line_length;
	// TODO bool modified;
	t_map		map;
	t_params	params;
}	t_data;

void	black_background(t_data *data);
int		close_window(t_data *data);
bool	get_map_dimensions(char *filename, t_map *map);
int		handle_key_down(int keycode, t_data *data);
bool	init_grid(void ***grid, size_t width, size_t height, size_t size);
void	init_map(t_map *map);
void	init_params(t_params *params);
void	line(t_data *data, int x0, int y0, int c0, int x1, int y1, int c1);
bool	parse_map(char *filename, t_map *map);
void	pixel_put(t_data *data, int x, int y, int color);

#endif