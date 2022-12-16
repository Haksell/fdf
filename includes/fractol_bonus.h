/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:06:02 by axbrisse          #+#    #+#             */
/*   Updated: 2022/12/16 02:56:43 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include "mlx.h"

# include <math.h>
# include <stdbool.h>

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 800
# define ESCAPE_RADIUS_SQUARED 100
# define ZOOM_FACTOR 1.1
# define BLACK 0x000000
# define WHITE 0xffffff

typedef enum e_fractal {
	MANDELBROT = 0,
	JULIA = 1
}	t_fractal;

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
	ESC = 65307,
};

enum {
	SCROLL_UP = 4,
	SCROLL_DOWN = 5,
};

typedef struct s_args {
	t_fractal	fractal;
	double		julia_start_x;
	double		julia_start_y;
}	t_args;

typedef struct s_limits {
	double	min_x;
	double	max_x;
	double	min_y;
	double	max_y;
}	t_limits;

typedef struct s_data {
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			endian;
	int			line_length;
	int			max_iterations;
	t_args		args;
	t_limits	limits;
}	t_data;

typedef int	(*t_iteration_func)(double, double, t_data *);

void	calculate_pixel(t_data *data, int x, int y, t_iteration_func func);
int		close_window(t_data *data);
int		get_color_0(int iterations, int max_iterations);
int		get_color_1(int iterations, int max_iterations);
int		get_color_2(int iterations, int max_iterations);
int		get_color_3(int iterations, int max_iterations);
int		get_color_4(int iterations, int max_iterations);
int		get_color_5(int iterations, int max_iterations);
int		get_color_6(int iterations, int max_iterations);
int		get_color_7(int iterations, int max_iterations);
int		get_color_8(int iterations, int max_iterations);
int		get_color_9(int iterations, int max_iterations);
int		handle_key_down(int keycode, t_data *data);
int		handle_zoom(int button, int x, int y, t_data *data);
int		iterations_julia(double x0, double y0, t_data *data);
int		iterations_mandelbrot(double x0, double y0, t_data *data);
bool	parse_args(int argc, char **argv, t_args *args);
double	scale_x(int x, t_data *data);
double	scale_y(int y, t_data *data);

#endif