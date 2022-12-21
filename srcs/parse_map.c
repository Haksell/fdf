/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 06:27:14 by axbrisse          #+#    #+#             */
/*   Updated: 2022/12/21 06:31:12 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static bool	endswith(char *s, char *end)
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

static void	finish_reading_file(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
		line = get_next_line(fd);
	close(fd);
}

static bool	parse_cell(char *cell, t_map *map, size_t x, size_t y)
{
	map->zs[y][x] = ft_atoi(cell);
	map->colors[y][x] = DEFAULT_COLOR;
	return (true);
}

static bool	parse_row(size_t y, char *line, t_map *map)
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

bool	parse_map(char *filename, t_map *map)
{
	int		fd;
	char	*line;
	size_t	y;

	if (!endswith(filename, ".fdf"))
		return (false);
	fd = open(filename, O_RDONLY);
	if (fd < 0 || !get_map_dimensions(filename, map)
		|| !initialize_grid(&map->zs, map->width, map->height)
		|| !initialize_grid(&map->colors, map->width, map->height))
		return (false);
	y = 0;
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
	return (true);
}