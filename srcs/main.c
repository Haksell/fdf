/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:04:35 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/07 13:47:48 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	reset_background(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			data->colors[y][x].color = BACKGROUND;
			data->colors[y][x].z = -INFINITY;
			++x;
		}
		++y;
	}
}

void	put_colors_to_image(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			pixel_put(data, x, y, data->colors[y][x].color);
			++x;
		}
		++y;
	}
}

int	render_frame(t_data *data)
{
	t_vertex	**vertices;

	if (!data->should_rerender)
		return (EXIT_SUCCESS);
	vertices = copy_vertices(data);
	if (vertices == NULL)
		close_window(data);
	reset_background(data);
	transform_vertices(data, vertices);
	put_lines(data, vertices);
	put_colors_to_image(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	data->should_rerender = false;
	ft_free_double_pointer((void ***)&vertices, data->map.height);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	char	*filename;
	t_data	data;

	ft_bzero(&data, sizeof(data));
	data.is_bonus = ft_endswith(argv[0], "bonus");
	data.projection = ISOMETRIC;
	data.should_rerender = true;
	filename = argv[1];
	if (argc != 2 || !ft_endswith(filename, ".fdf"))
		return (complain(&data, "Usage: ./fdf *.fdf"));
	if (!parse_map(filename, &data.map))
		return (complain(&data, "Failed to parse the map"));
	data.colors = init_vertices(WINDOW_WIDTH, WINDOW_HEIGHT);
	if (data.colors == NULL)
		return (complain(&data, "Failed to initialize colors"));
	if (!init_minilibx(&data, filename))
		return (complain(&data, "Failed to initialize mlx"));
	init_params(&data);
	mlx_hook(data.win, ON_DESTROY, NO_EVENT_MASK, close_window, &data);
	mlx_hook(data.win, ON_KEY_DOWN, KEY_PRESS_MASK, handle_key_down, &data);
	mlx_hook(data.win, ON_MOUSE_DOWN, B_PRESS_MASK, handle_mouse_down, &data);
	mlx_hook(data.win, ON_MOUSE_UP, B_RELEASE_MASK, handle_mouse_up, &data);
	mlx_loop_hook(data.mlx, &render_frame, &data);
	mlx_loop(data.mlx);
	return (EXIT_SUCCESS);
}
