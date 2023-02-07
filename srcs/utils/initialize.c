/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 05:45:51 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/07 15:56:08 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_params(t_data *data)
{
	t_vertex	origin;

	ft_bzero(&origin, sizeof(origin));
	data->params.scale = (0.5 * get_min(WINDOW_WIDTH, WINDOW_HEIGHT)
			/ get_max((double)data->map.width, (double)data->map.height));
	data->params.altitude = 1.0;
	data->params.rx = 0.0;
	data->params.ry = 0.0;
	data->params.rz = 0.0;
	data->params.tx = 0;
	data->params.ty = 0;
	transform_vertex(&origin, data);
	data->params.tx = WINDOW_WIDTH / 2.0 - origin.x;
	data->params.ty = WINDOW_HEIGHT / 2.0 - origin.y;
}

bool	init_minilibx(t_data *data, char *window_title)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		return (false);
	data->win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			window_title);
	if (data->win == NULL)
		return (false);
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (data->img == NULL)
		return (false);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	if (data->addr == NULL)
		return (false);
	return (true);
}

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
			ft_free_double_pointer((void ***)&vertices, i);
			return (NULL);
		}
		++i;
	}
	return (vertices);
}
