/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 04:42:40 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/04 05:50:02 by axbrisse         ###   ########.fr       */
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
# define EPSILON 1e-9
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 800
# define WHITE 0xffffff
# define BLACK 0x000000
# define TRANSLATION 10.0
# define ALTITUDE_SHIFT 1.1
# define SCALE_SHIFT 1.1
# define ANGLE_SHIFT (M_PI / 20)
# define SPACES " \t\n\v\f\r"

enum {
	ON_KEY_DOWN = 2,
	ON_MOUSE_DOWN = 4,
	ON_DESTROY = 17
};

enum {
	NO_EVENT_MASK = 0,
	KEY_PRESS_MASK = 1,
	BUTTON_PRESS_MASK = 4
};

enum {
	SCROLL_UP = 4,
	SCROLL_DOWN = 5
};

enum {
	KEY_ESC = 65307,
	KEY_LEFT = 65361,
	KEY_UP = 65362,
	KEY_RIGHT = 65363,
	KEY_DOWN = 65364
};

typedef struct s_vertex {
	double	x;
	double	y;
	double	z;
	int		color;
}	t_vertex;

typedef struct s_map {
	t_vertex	**vertices;
	int			height;
	int			width;
}	t_map;

typedef struct s_params {
	double	altitude;
	double	scale;
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
	bool		should_rerender;
	t_map		map;
	t_params	params;
}	t_data;

void	black_background(t_data *data);
int		close_window(t_data *data);
bool	get_map_dimensions(char *filename, t_map *map);
int 	get_min(int n1, int n2);
int		handle_key_down(int keycode, t_data *data);
int		handle_mouse_down(int button, int x, int y, t_data *data);
bool	init_grid(void ***grid, size_t width, size_t height, size_t size);
void	init_params(t_data *data);
void	put_lines(t_data *data, t_vertex **copy);
bool	parse_map(char *filename, t_map *map);
void	pixel_put(t_data *data, int x, int y, int color);

#endif