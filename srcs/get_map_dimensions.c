/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_dimensions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 05:49:25 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/07 10:33:31 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

bool	get_map_dimensions(char *filename, t_map *map)
{
	const int	fd = open(filename, O_RDONLY);
	char		*line;
	bool		return_value;

	if (fd < 0)
		return (false);
	line = get_next_line(fd);
	if (line == NULL)
		return (false);
	map->width = ft_num_words(line, SPACES);
	map->height = 0;
	return_value = true;
	while (line != NULL)
	{
		if (ft_num_words(line, SPACES) != (size_t)map->width)
			return_value = false;
		++map->height;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (return_value && map->height >= 2 && map->width >= 2);
}
