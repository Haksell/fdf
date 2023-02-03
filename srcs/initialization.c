/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 05:45:51 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/03 01:18:58 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

bool	init_grid(void ***grid, size_t width, size_t height, size_t size)
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

void	init_map(t_map *map)
{
	map->height = 0;
	map->width = 0;
	map->zs = NULL;
	map->colors = NULL;
}

void	init_params(t_params *params)
{
	params->z_factor = DEFAULT_Z_FACTOR;
	params->zoom = 1.0;
	params->tx = 0.0;
	params->ty = 0.0;
	params->rx = 0.0;
	params->ry = 0.0;
	params->rz = 0.0;
}
