/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 05:45:51 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/03 04:40:56 by axbrisse         ###   ########.fr       */
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

void	init_params(t_data *data)
{
	data->params.altitude = DEFAULT_ALTITUDE;
	data->params.scale = get_min(WINDOW_WIDTH / data->map.width, WINDOW_HEIGHT / data->map.height) / 2;
	data->params.tx = (WINDOW_WIDTH - 1) / 2.0;
	data->params.ty = (WINDOW_HEIGHT - 1) / 2.0;
	data->params.rx = 0.0;
	data->params.ry = 0.0;
	data->params.rz = 0.0;
}
