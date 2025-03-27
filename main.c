/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:21:32 by mgonzaga          #+#    #+#             */
/*   Updated: 2025/03/27 19:41:36 by sabrifer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

int	main(int argc, char **argv)
{
	t_game		*game;
	char		**file_matrix;

	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return (1);
	if (!check_arguments(argc, argv[1]))
		return (1);
	file_matrix = makematrix(argv[1], countcols(argv[1]));
	if (!validate_content(file_matrix))
		return (1);
	game->map = malloc(sizeof(t_content));
	if (!get_content(file_matrix, game->map))
		return (1);
	init_game(game);
	cleanup_program(game);
	return (0);
}
