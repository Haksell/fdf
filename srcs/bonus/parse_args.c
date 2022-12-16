/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 18:17:42 by axbrisse          #+#    #+#             */
/*   Updated: 2022/12/16 22:09:13 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

static bool	ft_atod(const char *s, double *ans)
{
	size_t	i;
	double	sign;
	double	decimal;

	i = s[0] == '-';
	sign = (s[0] != '-') - (s[0] == '-');
	*ans = 0.0;
	while (ft_isdigit(s[i]))
		*ans = 10 * *ans + s[i++] - '0';
	if (s[i] == '.')
	{
		++i;
		decimal = 1.0;
		while (ft_isdigit(s[i]))
		{
			decimal /= 10;
			*ans += decimal * (s[i++] - '0');
		}
	}
	*ans *= sign;
	return (s[i] == '\0');
}

bool	parse_args_4(char **argv, t_args *args)
{
	if (ft_strcmp(argv[1], "julia") == 0
		&& ft_atod(argv[2], &args->julia_start_x)
		&& ft_atod(argv[3], &args->julia_start_y))
	{
		args->fractal = JULIA;
		args->julia_follows_mouse = false;
		return (true);
	}
	return (false);
}

bool	parse_args_2(char **argv, t_args *args)
{
	if (ft_strcmp(argv[1], "mandelbrot") == 0)
		args->fractal = MANDELBROT;
	else if (ft_strcmp(argv[1], "julia") == 0)
	{
		args->fractal = JULIA;
		args->julia_follows_mouse = true;
	}
	else if (ft_strcmp(argv[1], "tricorn") == 0)
		args->fractal = TRICORN;
	else if (ft_strcmp(argv[1], "burning_ship") == 0)
		args->fractal = BURNING_SHIP;
	else if (ft_strcmp(argv[1], "cactus") == 0)
		args->fractal = CACTUS;
	else if (ft_strcmp(argv[1], "hmmm") == 0)
		args->fractal = HMMM;
	else
		return (false);
	return (true);
}

bool	parse_args(int argc, char **argv, t_args *args)
{
	if (argc == 2)
		return parse_args_2(argv, args);
	else if (argc == 4)
		return parse_args_4(argv, args);
	return (false);
}
