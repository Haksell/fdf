/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:04:35 by axbrisse          #+#    #+#             */
/*   Updated: 2022/12/16 02:38:51 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	set_limits(t_data *data)
{
	static t_limits	limits[] = {
	{-2.25, 0.75, -1.5, 1.5},
	{-1.5, 1.5, -1.5, 1.5}};

	data->limits = limits[data->args.fractal];
}

static int	render_frame(t_data *data)
{
	static t_iteration_func	funcs[] = {
		iterations_mandelbrot, iterations_julia
	};
	const t_iteration_func	func = funcs[data->args.fractal];
	int						x;
	int						y;

	y = -1;
	while (++y < WINDOW_HEIGHT)
	{
		x = -1;
		while (++x < WINDOW_WIDTH)
			calculate_pixel(data, x, y, func);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!parse_args(argc, argv, &data.args))
	{
		ft_putendl_fd("Usage:", STDERR_FILENO);
		ft_putendl_fd("- ./fractol mandelbrot", STDERR_FILENO);
		ft_putendl_fd("- ./fractol julia real imag", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	set_limits(&data);
	data.max_iterations = 100;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, argv[0]);
	data.img = mlx_new_image(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
			&data.line_length, &data.endian);
	mlx_hook(data.win, ON_DESTROY, NO_EVENT_MASK, close_window, &data);
	mlx_hook(data.win, ON_KEY_DOWN, KEY_PRESS_MASK, handle_key_down, &data);
	mlx_hook(data.win, ON_MOUSE_DOWN, BUTTON_PRESS_MASK, handle_zoom, &data);
	mlx_loop_hook(data.mlx, &render_frame, &data);
	mlx_loop(data.mlx);
	return (EXIT_SUCCESS);
}
