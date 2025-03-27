/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrifer <sabrifer@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:49:43 by sabrifer          #+#    #+#             */
/*   Updated: 2025/03/23 12:28:55 by sabrifer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

void	draw_walls_with_texture(int x, t_game *game)
{
	mlx_texture_t	*texture;

	texture = get_wall_texture(game);
	calculate_x_for_vertical_slice(game, texture->width);
	calculate_texture_step_and_position(game, texture->height);
	calculate_and_draw_walls(game, texture, x);
}

void	clear_image(t_game *game)
{

	int				i;
	int				j;
	unsigned int	blank;

	i = 0;
	j = 0;
	blank = 0xFFFFFFFF;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
				mlx_put_pixel(game->img, i, j, blank);
			j++;
		}
		i++;
	}
}

void	render_raycast_frame(void *param)
{
	t_game	*game;
	int	x;

	x = 0;
	game = (t_game *)param;
	clear_image(game);
	draw_ceiling_and_floor(game);
	//while (x < WIDTH)
	//{
	//	// check the functions beings called and if it makes sense
	//	calculate_rays(x, game);
	//	get_wall_height(game->ray);
	//	draw_walls_with_texture(x, game);
	//	x++;
	//}
	mlx_image_to_window(game->mlx, game->img, 0, 0);
}

int	init_game(t_game *game)
{
	if (!init_window(game))
		return (print_error(ERROR_16));
	if (!init_structs_in_game(game))
		return (print_error(ERROR_3));
	mlx_key_hook(game->mlx, &key_pressed_function, game);
	mlx_loop_hook(game->mlx, render_raycast_frame, game);
	mlx_loop(game->mlx);
	mlx_delete_texture(game->textures->NO_path);
	mlx_delete_texture(game->textures->SO_path);
	mlx_delete_texture(game->textures->WE_path);
	mlx_delete_texture(game->textures->EA_path);
	free(game->textures);
	free(game->ray);
	free(game->player);
	mlx_terminate(game->mlx);
	return (1);
}
