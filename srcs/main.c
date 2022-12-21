/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:04:35 by axbrisse          #+#    #+#             */
/*   Updated: 2022/12/21 05:33:58 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_window(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
	return (0);
}

int	handle_key_down(int keycode, t_data *data)
{
	if (keycode == ESC)
		close_window(data);
	return (0);
}

void	pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	dst = data->addr + data->line_length * y + data->bits_per_pixel / 8 * x;
	*(unsigned int *)dst = color;
}

int	render_frame(t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

bool	endswith(char *s, char *end)
{
	const size_t	s_len = ft_strlen(s);
	const size_t	end_len = ft_strlen(end);
	size_t			i;

	if (end_len > s_len)
		return (false);
	i = 1;
	while (i <= end_len)
	{
		if (s[s_len - i] != end[end_len - i])
			return (false);
		++i;
	}
	return (true);
}

bool	get_map_height(char *filename, t_map *map)
{
	const int	fd = open(filename, O_RDONLY);
	char		*line;

	ft_printf("height\n");
	if (fd < 0)
		return (false);
	line = get_next_line(fd);
	while (line != NULL)
	{
		++map->height;
		line = get_next_line(fd);
	}
	close(fd);
	return (true);
}

bool	get_map_width(char *filename, t_map *map)
{
	const int	fd = open(filename, O_RDONLY);
	char		*line;

	ft_printf("width\n");
	if (fd < 0)
		return (false);
	ft_printf("width\n");
	line = get_next_line(fd);
	if (line == NULL)
		return (false);
	ft_printf("width\n");
	map->width = ft_num_words(line, ' ');
	free(line);
	close(fd);
	return (true);
}

bool	parse_cell(char *cell, t_map *map, size_t x, size_t y)
{
	map->zs[y][x] = ft_atoi(cell);
	map->colors[y][x] = DEFAULT_COLOR;
	return (true);
}

bool	parse_row(size_t y, char *line, t_map *map)
{
	char	**cells;
	size_t	x;

	if (ft_num_words(line, ' ') != map->width)
		return (false);
	cells = ft_split(line, ' ');
	if (cells == NULL)
		return (false);
	x = 0;
	while (x < map->width)
	{
		if (!parse_cell(cells[x], map, x, y))
		{
			ft_free_double_pointer((void **)cells, map->width);
			return (false);
		}
		++x;
	}
	ft_free_double_pointer((void **)cells, map->width);
	return (true);
}

void	finish_reading_file(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
		line = get_next_line(fd);
	close(fd);
}

bool	initialize_grid(int ***grid, size_t width, size_t height)
{
	size_t	i;

	ft_printf("grid\n");
	*grid = malloc(sizeof(int *) * height);
	if (*grid == NULL)
		return (false);
	i = 0;
	while (i < height)
	{
		(*grid)[i] = malloc(sizeof(int) * width);
		if ((*grid)[i] == NULL)
		{
			ft_free_double_pointer((void **)*grid, i);
			return (false);
		}
		++i;
	}
	return (true);
}

bool	parse_map(char *filename, t_map *map)
{
	const int	fd = open(filename, O_RDONLY);
	char		*line;
	size_t		y;

	ft_printf("hmmm1\n");
	if (fd < 0 || !get_map_height(filename, map) || !get_map_width(filename, map)
		|| !initialize_grid(&map->zs, map->width, map->height)
		|| !initialize_grid(&map->colors, map->width, map->height))
		return (false);
	y = 0;
	ft_printf("hmmm2\n");
	while (y < map->height)
	{
		line = get_next_line(fd);
		if (line == NULL || !parse_row(y, line, map))
		{
			ft_free_double_pointer((void **)map->zs, y);
			ft_free_double_pointer((void **)map->colors, y);
			finish_reading_file(fd);
			return (false);
		}
		++y;
	}
	close(fd);
	ft_printf("hmmm3\n");
	return (true);
}

void	initialize_map(t_map *map)
{
	map->height = 0;
	map->width = 0;
	map->zs = NULL;
	map->colors = NULL;
}

int	main(int argc, char **argv)
{
	t_data	data;

	initialize_map(&data.map);
	if (argc != 2 || !endswith(argv[1], ".fdf") || !parse_map(argv[1], &data.map))
	{
		ft_putendl_fd("Usage: ./fdf *.fdf", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, argv[0]);
	data.img = mlx_new_image(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	mlx_hook(data.win, ON_DESTROY, NO_EVENT_MASK, close_window, &data);
	mlx_hook(data.win, ON_KEY_DOWN, KEY_PRESS_MASK, handle_key_down, &data);
	mlx_loop_hook(data.mlx, &render_frame, &data);
	mlx_loop(data.mlx);
	return (EXIT_SUCCESS);
}
