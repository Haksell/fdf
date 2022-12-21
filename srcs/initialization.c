/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 05:45:51 by axbrisse          #+#    #+#             */
/*   Updated: 2022/12/21 05:46:13 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

bool	initialize_grid(int ***grid, size_t width, size_t height)
{
	size_t	i;

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

void	initialize_map(t_map *map)
{
	map->height = 0;
	map->width = 0;
	map->zs = NULL;
	map->colors = NULL;
}