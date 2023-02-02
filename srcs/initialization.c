/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 05:45:51 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/03 00:07:31 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

bool	initialize_grid(void ***grid, size_t width, size_t height, size_t size)
{
	size_t	i;

	*grid = malloc(sizeof(void *) * (height + 1));
	if (*grid == NULL)
		return (false);
	grid[height] = NULL;
	i = 0;
	while (i < height)
	{
		(*grid)[i] = ft_calloc(width, size);
		if ((*grid)[i] == NULL)
		{
			ft_free_double_pointer(*grid, i);
			return (false);
		}
		++i;
	}
	return (true);
}

void	initialize_map(t_map *map)
{
	map->height = 0;
	map->width = 0;
	map->zs = NULL;
	map->colors = NULL;
}