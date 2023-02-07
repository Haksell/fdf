/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 06:27:14 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/07 12:22:33 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static bool	parse_double(const char *s, double *ans)
{
	size_t	i;
	double	sign;
	double	decimal;

	i = s[0] == '-';
	sign = (s[0] != '-') - (s[0] == '-');
	*ans = 0.0;
	while (ft_isdigit(s[i]))
		*ans = 10 * *ans + s[i++] - '0';
	if (s[i] == '.')
	{
		++i;
		decimal = 0.1;
		while (ft_isdigit(s[i]))
		{
			*ans += decimal * (s[i] - '0');
			decimal /= 10;
			i++;
		}
	}
	*ans *= sign;
	return (s[i] == '\0');
}

static bool	parse_color(const char *s, int *color)
{
	int	i;

	if ((ft_strncmp(s, "0x", 2) != 0) || (s[2] == '\0'))
		return (false);
	*color = 0;
	i = 2;
	while (s[i] != '\0')
	{
		*color <<= 4;
		if (*color > WHITE)
			return (false);
		else if (ft_isdigit(s[i]))
			*color |= s[i] - 48;
		else if ('A' <= s[i] && s[i] <= 'F')
			*color |= s[i] - 55;
		else if ('a' <= s[i] && s[i] <= 'f')
			*color |= s[i] - 87;
		else
			return (false);
		++i;
	}
	return (true);
}

static bool	parse_cell(char *cell, t_map *map, int x, int y)
{
	const char	*comma = ft_strchr(cell, ',');
	int			i;

	map->vertices[y][x].x = x - (map->width - 1) / 2;
	map->vertices[y][x].y = y - (map->height - 1) / 2;
	if (comma == NULL)
	{
		map->vertices[y][x].color = WHITE;
		return (parse_double(cell, &map->vertices[y][x].z));
	}
	else
	{
		i = comma - cell;
		cell[i] = '\0';
		return (
			parse_double(cell, &map->vertices[y][x].z)
			&& parse_color(cell + i + 1, &map->vertices[y][x].color)
		);
	}
}

static bool	parse_row(int y, char *line, t_map *map)
{
	char	**cells;
	bool	is_valid_row;
	char	*trimmed;
	int		x;

	is_valid_row = true;
	trimmed = ft_strtrim(line, SPACES);
	if (trimmed == NULL || ft_num_words(trimmed, SPACES) != (size_t)map->width)
		return (free(trimmed), false);
	cells = ft_split_set(trimmed, SPACES);
	free(trimmed);
	if (cells == NULL)
		return (false);
	x = 0;
	while (is_valid_row && x < map->width)
	{
		if (!parse_cell(cells[x], map, x, y))
			is_valid_row = false;
		++x;
	}
	ft_free_double_pointer((void **)cells, map->width);
	return (is_valid_row);
}

bool	parse_map(char *filename, t_map *map)
{
	int		fd;
	char	*line;
	int		y;
	bool	is_valid_map;

	fd = open(filename, O_RDONLY);
	if (fd < 0 || !get_map_dimensions(filename, map))
		return (close(fd), false);
	map->vertices = init_vertices(map->width, map->height);
	if (map->vertices == NULL)
		return (close(fd), false);
	is_valid_map = true;
	y = 0;
	while (is_valid_map && y < map->height)
	{
		line = get_next_line(fd);
		is_valid_map = line != NULL && parse_row(y, line, map);
		free(line);
		++y;
	}
	close(fd);
	if (!is_valid_map)
		ft_free_double_pointer((void **)map->vertices, map->height);
	return (is_valid_map);
}
