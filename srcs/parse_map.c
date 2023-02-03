/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 06:27:14 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/03 00:54:46 by axbrisse         ###   ########.fr       */
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

	if (ft_strncmp(s, "0x", 2) != 0)
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

	if (comma == NULL)
	{
		map->colors[y][x] = WHITE;
		return (parse_double(cell, &map->zs[y][x]));
	}
	else
	{
		i = comma - cell;
		cell[i] = '\0';
		return (
			parse_double(cell, &map->zs[y][x])
			&& parse_color(cell + i + 1, &map->colors[y][x])
		);
	}
}

static bool	parse_row(int y, char *line, t_map *map)
{
	char	**cells;
	bool	return_value;
	char	*trimmed;
	int		x;

	return_value = true;
	trimmed = ft_strtrim(line, SPACES);
	// free(line);
	if (trimmed == NULL || ft_num_words(trimmed, SPACES) != (size_t)map->width)
		return (false);
	cells = ft_split_set(trimmed, SPACES);
	// free(trimmed);
	if (cells == NULL)
		return (false);
	x = 0;
	while (return_value && x < map->width)
	{
		if (!parse_cell(cells[x], map, x, y))
			return_value = false;
		++x;
	}
	// ft_free_double_pointer((void **)cells, map->width);
	return (return_value);
}

bool	parse_map(char *filename, t_map *map)
{
	int		fd;
	char	*line;
	int		y;
	bool	return_value;

	if (!ft_endswith(filename, ".fdf"))
		return (false);
	fd = open(filename, O_RDONLY);
	return_value = (fd >= 3 && get_map_dimensions(filename, map)
			&& init_grid((void ***)&map->zs, map->width, map->height, sizeof(double))
			&& init_grid((void ***)&map->colors, map->width, map->height, sizeof(int)));
	y = 0;
	while (return_value && y < map->height)
	{
		line = get_next_line(fd);
		if (line == NULL || !parse_row(y, line, map))
			return_value = false;
		++y;
	}
	// ft_free_double_pointer((void **)map->zs, map->height);
	// ft_free_double_pointer((void **)map->colors, map->height);
	close(fd);
	return (return_value);
}
