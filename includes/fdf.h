/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 04:42:40 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/07 02:15:47 by axbrisse         ###   ########.fr       */
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
# define BACKGROUND 0x111111
# define TRANSLATION 10.0
# define ALTITUDE_SHIFT 1.1
# define SCALE_SHIFT 1.1
# define ISOMETRIC_COS 0.8660254037844387
# define ISOMETRIC_SIN 0.5
# define CABINET_COS 0.4472135954999580
# define CABINET_SIN 0.8944271909999159
# define ANGLE_SHIFT (M_PI / 20)
# define SPACES " \t\n\v\f\r"
# define MIN_NUMPAD 65429
# define MAX_NUMPAD 65438
# define MAX_PROJECTION ISOMETRIC

enum {
	ON_KEY_DOWN = 2,
	ON_MOUSE_DOWN = 4,
	ON_MOUSE_UP = 5,
	ON_DESTROY = 17
};

enum {
	NO_EVENT_MASK = 0,
	KEY_PRESS_MASK = 1,
	BUTTON_PRESS_MASK = 4,
	BUTTON_RELEASE_MASK = 8
};

enum {
	BUTTON_LEFT = 1,
	SCROLL_UP = 4,
	SCROLL_DOWN = 5
};

enum {
	KEY_ESC = 65307,
	KEY_HOME = 65360,
	KEY_LEFT = 65361,
	KEY_UP = 65362,
	KEY_RIGHT = 65363,
	KEY_DOWN = 65364
};

typedef enum e_projection {
	CABINET = 0,
	PARALLEL,
	ISOMETRIC,
}	t_projection;

typedef struct s_vertex {
	double	x;
	double	y;
	double	z;
	int		color;
}	t_vertex;

typedef struct s_int_vertex {
	int	x;
	int	y;
	int	z;
	int	color;
}	t_int_vertex;

typedef struct s_position {
	int	x;
	int	y;
}	t_position;

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
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				endian;
	int				line_length;
	bool			should_rerender;
	t_vertex		**colors;
	t_position		mouse;
	t_map			map;
	t_params		params;
	t_projection	projection;
}	t_data;

typedef void	(*t_project_func)(t_vertex *, t_data *);

void	redraw_background(t_data *data);
int		close_window(t_data *data);
bool	get_map_dimensions(char *filename, t_map *map);
int		handle_key_down(int keycode, t_data *data);
int		handle_mouse_down(int button, int x, int y, t_data *data);
int		handle_mouse_up(int button, int x, int y, t_data *data);
bool	init_minilibx(t_data *data, char *window_title);
void	init_params(t_data *data);
void	put_lines(t_data *data, t_vertex **copy);
bool	parse_map(char *filename, t_map *map);
void	pixel_put(t_data *data, int x, int y, int color);

void	rotate_2d(double *d1, double *d2, double rotation);
void	scale_vertex(t_vertex *vertex, double scale);
void	rotate_vertex(t_vertex *vertex, double rx, double ry, double rz);
void	translate_vertex(t_vertex *vertex, double tx, double ty);
void	transform_vertex(t_vertex *vertex, t_data *data);
void	transform_vertices(t_data *data, t_vertex **copy);
void	inverse_transform_vertex(t_vertex *vertex, t_data *data);

// create_vertices.c
t_vertex	**init_vertices(int width, int height);
t_vertex	**copy_vertices(t_data *data);

// projections.c
void	project_vertex(t_vertex *vertex, t_data *data);
void	inverse_project_vertex(t_vertex *vertex, t_data *data);

// rotations.c
void		rotate_2d(double *d1, double *d2, double rotation);
void		rotate_vertex(t_vertex *vertex, double rx, double ry, double rz);
void		inverse_rotate_vertex(t_vertex *vertex, double rx, double ry, double rz);

// utils.c
int			complain(t_data *data, char *error_message);
void		free_data(t_data *data);
double		get_max(double x1, double x2);
double		get_min(double x1, double x2);
int			get_sign(int n);

#endif