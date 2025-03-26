/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_init_structs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrifer <sabrifer@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:49:43 by sabrifer          #+#    #+#             */
/*   Updated: 2025/03/25 13:52:37 by sabrifer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

int	init_structs_in_game(t_game *game)
{
	game->img = init_img(game);
	if (!game->img)
		return (0);
	game->ray = (t_ray *)malloc(sizeof(t_ray));
	if (!game->ray)
	{
		mlx_delete_image(game->mlx, game->img);
		return (print_error(ERROR_3));
	}
	game->player = init_player_struct(game->map);
	if (!game->player)
	{
		mlx_delete_image(game->mlx, game->img);
		free(game->ray);
	}
	game->textures = init_textures(game);
	if (!game->textures)
	{
		mlx_delete_image(game->mlx, game->img);
		free(game->ray);
		free(game->player);
		return (print_error(ERROR_3));
	}
	return (1);
}
