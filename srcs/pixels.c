/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 18:22:58 by axbrisse          #+#    #+#             */
/*   Updated: 2022/12/15 21:24:33 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	dst = data->addr + data->line_length * y + data->bits_per_pixel / 8 * x;
	*(unsigned int *)dst = color;
}

int	get_color(int iterations, int max_iterations)
{
	static int	colors[] = {0x67001f, 0x6d0120, 0x760421, 0x7c0622,
		0x840923, 0x8a0b24, 0x930e26, 0x9c1127, 0xa21228, 0xab1529, 0xb1172a,
		0xb61f2e, 0xba2732, 0xbd2d35, 0xc13539, 0xc43b3b, 0xc8443f, 0xcb4942,
		0xcf5246, 0xd45a4a, 0xd6604d, 0xda6853, 0xdc6d57, 0xe0765d, 0xe37e64,
		0xe68368, 0xe98b6e, 0xec9172, 0xef9979, 0xf29e7d, 0xf5a683, 0xf6ad8c,
		0xf6b191, 0xf7b799, 0xf8bb9f, 0xf9c2a7, 0xfac8af, 0xfbccb4, 0xfcd3bc,
		0xfdd7c2, 0xfeddc9, 0xfee1d0, 0xfee4d5, 0xfee8db, 0xfeebe0, 0xffefe6,
		0xfff2eb, 0xfff6f1, 0xfffbf8, 0xfffdfc, 0xfefefe, 0xfbfbfb, 0xf8f8f8,
		0xf4f4f4, 0xf1f1f1, 0xeeeeee, 0xebebeb, 0xe8e8e8, 0xe5e5e5, 0xe2e2e2,
		0xdddddd, 0xdadada, 0xd6d6d6, 0xd3d3d3, 0xcecece, 0xcacaca, 0xc7c7c7,
		0xc2c2c2, 0xbfbfbf, 0xbbbbbb, 0xb5b5b5, 0xb1b1b1, 0xababab, 0xa7a7a7,
		0xa1a1a1, 0x9d9d9d, 0x979797, 0x919191, 0x8d8d8d, 0x878787, 0x828282,
		0x7c7c7c, 0x757575, 0x707070, 0x696969, 0x656565, 0x5e5e5e, 0x595959,
		0x535353, 0x4c4c4c, 0x484848, 0x424242, 0x3e3e3e, 0x383838, 0x323232,
		0x2e2e2e, 0x282828, 0x242424, 0x1e1e1e, 0x1a1a1a};
	const	int num_colors = sizeof(colors) / sizeof(int);

	if (iterations == max_iterations)
		return (BLACK);
	else
		return (colors[iterations * num_colors / max_iterations]);
}

void	calculate_pixel(t_data *data, int x, int y, t_iteration_func func)
{
	pixel_put(data, x, y, get_color(
			func(scale_x(x, data), scale_y(y, data), data), data->max_iterations));
}
