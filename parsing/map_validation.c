/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:34:53 by mgonzaga          #+#    #+#             */
/*   Updated: 2025/03/20 16:37:31 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_3d.h"

int validate_map(t_args *s_map)
{
	s_map->map_position = find_map(s_map);	
	if(!find_player(s_map))
		return(print_error(ERROR_11));
	if(!invalid_character(s_map, s_map->map_position))
		return(print_error(ERROR_13));
	if(!validate_wall(s_map))
		return(print_error(ERROR_12));
	if(!empty_line(s_map))
		return(print_error(ERROR_14));
	return(1);
}

