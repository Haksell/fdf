/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 04:41:05 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/06 08:21:02 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	complain(t_data *data, char *error_message)
{
	free_data(data);
	ft_putendl_fd(error_message, STDERR_FILENO);
	return (EXIT_FAILURE);
}

void	free_data(t_data *data)
{
	ft_free_double_pointer((void **)data->map.vertices, data->map.height);
	ft_free_double_pointer((void **)data->colors, WINDOW_HEIGHT);
}

double	get_min(double x1, double x2)
{
	if (x1 < x2)
		return (x1);
	else
		return (x2);
}

double	get_max(double x1, double x2)
{
	if (x1 > x2)
		return (x1);
	else
		return (x2);
}

int	get_sign(int n)
{
	return ((n > 0) - (n < 0));
}
