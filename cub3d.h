/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:44:46 by mgonzaga          #+#    #+#             */
/*   Updated: 2025/01/24 15:07:46 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H


# include "./libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

# define ERROR_1 "Impossible to read the file\n"
# define ERROR_2 "Empty Map\n"
# define ERROR_3 "Invalid malloc\n"

typedef struct s_map
{
	char **matrix;
	char	*name_file;
}t_map;

#endif 