/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 04:41:05 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/05 04:23:50 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	complain(char *error_message)
{
	ft_putendl_fd(error_message, STDERR_FILENO);
	return (EXIT_FAILURE);
}

double	get_min(double n1, double n2)
{
	if (n1 < n2)
		return (n1);
	else
		return (n2);
}
