/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_test.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 08:41:10 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/07 09:05:42 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_TEST_H
# define FDF_TEST_H

# include "fdf.h"

# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>

# define RESET "\033[0m"
# define BOLDBLUE "\033[1m\033[34m"
# define RED "\033[31m"
# define GREEN "\033[32m"

# define VALID_DIRECTORY "maps/valid/"
# define INVALID_DIRECTORY "maps/invalid/"

#endif
