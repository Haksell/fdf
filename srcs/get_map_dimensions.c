/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_dimensions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 05:49:25 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/02 22:00:30 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static bool	get_map_height(char *filename, t_map *map)
{
	const int	fd = open(filename, O_RDONLY);
	char		*line;

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

static bool	get_map_width(char *filename, t_map *map)
{
	const int	fd = open(filename, O_RDONLY);
	char		*line;

	if (fd < 0)
		return (false);
	line = get_next_line(fd);
	if (line == NULL)
		return (false);
	map->width = ft_num_words(line, " ");
	free(line);
	// TODO finish reading file(smarter to do all in one func)
	close(fd);
	return (true);
}

bool	get_map_dimensions(char *filename, t_map *map)
{
	return (get_map_height(filename, map) && get_map_width(filename, map));
}