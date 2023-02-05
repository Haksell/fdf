/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 05:45:51 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/05 07:24:23 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_params(t_data *data)
{
	t_vertex origin = {0, 0, 0, 0};

	data->params.scale = get_min(
			WINDOW_WIDTH / (double)data->map.width,
			WINDOW_HEIGHT / (double)data->map.height) / 2.0; // TODO different depending on projection
	project_vertex(&origin, data->map.height);
	data->params.tx = WINDOW_WIDTH / 2.0 - origin.x;
	data->params.ty = WINDOW_HEIGHT / 2.0 - origin.y;
	data->params.altitude = 1.0;
	data->params.rx = 0.0;
	data->params.ry = 0.0;
	data->params.rz = 0.0;
}

bool	init_minilibx(t_data *data, char *window_title)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		return (false);
	data->win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, window_title);
	if (data->win == NULL)
		return (false);
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (data->img == NULL)
		return (false);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	if (data->addr == NULL)
		return (false);
	return (true);
}
