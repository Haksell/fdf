/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 04:42:40 by axbrisse          #+#    #+#             */
/*   Updated: 2022/12/28 17:21:29 by axbrisse         ###   ########.fr       */
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

# ifndef M_PI
#  define M_PI 3.141592653589793
# endif

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 800
# define WHITE 0xffffff

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
	int				**colors;
	unsigned int	**zs;
	unsigned int	height;
	unsigned int	width;
	unsigned int	max_z;
}	t_map;

typedef struct s_data {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		endian;
	int		line_length;
	double	z_factor;
	t_map	map;
}	t_data;

int		close_window(t_data *data);
bool	get_map_dimensions(char *filename, t_map *map);
int		handle_key_down(int keycode, t_data *data);
bool	initialize_grid(int ***grid, size_t width, size_t height);
void	initialize_map(t_map *map);
bool	parse_map(char *filename, t_map *map);
void	line(t_data *data, int x0, int y0, int c0, int x1, int y1, int c1);

#endif