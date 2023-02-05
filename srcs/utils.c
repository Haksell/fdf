/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 04:41:05 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/05 05:02:10 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	complain(char *error_message)
{
	ft_putendl_fd(error_message, STDERR_FILENO);
	return (EXIT_FAILURE);
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
