/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_vertices.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 04:12:04 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/05 04:12:46 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vertex	**init_vertices(int width, int height)
{
	t_vertex	**vertices;
	int			i;

	vertices = malloc(sizeof(t_vertex *) * height);
	if (vertices == NULL)
		return (NULL);
	i = 0;
	while (i < height)
	{
		vertices[i] = ft_calloc(width, sizeof(t_vertex));
		if (vertices[i] == NULL)
		{
			ft_free_double_pointer((void **)vertices, i);
			return (NULL);
		}
		++i;
	}
	return (vertices);
}

t_vertex	**copy_vertices(t_data *data)
{
	t_vertex	**copy;
	int			x;
	int			y;

	copy = init_vertices(data->map.width, data->map.height);
	if (copy == NULL)
		return (NULL);
	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			copy[y][x] = data->map.vertices[y][x];
			copy[y][x].z *= data->params.altitude;
			++x;
		}
		++y;
	}
	return (copy);
}
