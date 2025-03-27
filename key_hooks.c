/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 14:14:24 by sabrifer          #+#    #+#             */
/*   Updated: 2025/03/26 14:01:49 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

void	key_pressed_function(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	(void)keydata;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_player_w(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_player_s(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_player_a(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_player_d(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		move_player_vision_left(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		move_player_vision_right(game);
}

void	move_player_w(t_game *game)
{
	double	new_x;
	double	new_y;
	int		new_pos_x;
	int		new_pos_y;

	new_y = game->player->pos_y + game->player->dir_y
		* MOVE_SPEED;
	new_x = game->player->pos_x + game->player->dir_x
		* MOVE_SPEED;
	new_pos_x = (int)new_x;
	new_pos_y = (int)new_y;
	if (game->map->map[new_pos_y][new_pos_x] != '1'
		&& new_x < game->map->map_max_x
		&& new_y < game->map->map_max_y)
	{
		game->player->pos_x = new_x;
		game->player->pos_y = new_y;
	}
}

void	move_player_s(t_game *game)
{
	double	new_x;
	double	new_y;
	int		new_pos_x;
	int		new_pos_y;

	new_y = game->player->pos_y - game->player->dir_y
		* MOVE_SPEED;
	new_x = game->player->pos_x - game->player->dir_x
		* MOVE_SPEED;
	new_pos_x = (int)new_x;
	new_pos_y = (int)new_y;
	if (game->map->map[new_pos_y][new_pos_x] != '1'
		&& new_x < game->map->map_max_x
		&& new_y < game->map->map_max_y)
	{
		game->player->pos_x = new_x;
		game->player->pos_y = new_y;
	}
}

void	move_player_a(t_game *game)
{
	double	new_x;
	double	new_y;
	int		new_pos_x;
	int		new_pos_y;

	new_y = game->player->pos_y - game->player->plane_y
		* MOVE_SPEED;
	new_x = game->player->pos_x - game->player->plane_x
		* MOVE_SPEED;
	new_pos_x = (int)new_x;
	new_pos_y = (int)new_y;
	if (game->map->map[new_pos_y][new_pos_x] != '1'
		&& new_x < game->map->map_max_x
		&& new_y < game->map->map_max_y)
	{
		game->player->pos_x = new_x;
		game->player->pos_y = new_y;
	}
}

void	move_player_d(t_game *game)
{
	double	new_x;
	double	new_y;
	int		new_pos_x;
	int		new_pos_y;

	new_y = game->player->pos_y + game->player->plane_y
		* MOVE_SPEED;
	new_x = game->player->pos_x + game->player->plane_x
		* MOVE_SPEED;
	new_pos_x = (int)new_x;
	new_pos_y = (int)new_y;
	if (game->map->map[new_pos_y][new_pos_x] != '1'
		&& new_x < game->map->map_max_x
		&& new_y < game->map->map_max_y)
	{
		game->player->pos_x = new_x;
		game->player->pos_y = new_y;
	}
}
