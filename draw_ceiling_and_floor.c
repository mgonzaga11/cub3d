/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ceiling_and_floor.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrifer <sabrifer@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:49:43 by sabrifer          #+#    #+#             */
/*   Updated: 2025/03/27 10:41:14 by sabrifer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

// Function to get the pixel color from a floor/ceiling texture
uint32_t	get_current_pixel_color_floor_ceiling(mlx_texture_t *texture,
		int tex_x, int tex_y)
{
	int		pixel_index;
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;
	uint8_t	alpha;

	pixel_index = (tex_y * texture->width + tex_x) * 4;
	red = texture->pixels[pixel_index];
	green = texture->pixels[pixel_index + 1];
	blue = texture->pixels[pixel_index + 2];
	alpha = texture->pixels[pixel_index + 3];
	return (ft_pixel(red, green, blue, alpha));
}

// Function to draw a floor or ceiling pixel
void	draw_ceiling(t_game *game, mlx_texture_t *texture, int tex_x,
		int tex_y, int screen_y)
{
	uint32_t	color;

	color = get_current_pixel_color_floor_ceiling(texture, tex_x, tex_y);
	if (screen_y >= 0 && screen_y < HEIGHT && tex_x >= 0 && tex_x < WIDTH)
	{
		mlx_put_pixel(game->img, tex_x, screen_y, color);
	}
}

void	draw_ceiling_and_floor(t_game *game)
{
	int				x;
	int				y;
	int				middle_line;
	mlx_texture_t	*texture;
	int				tx;
	int				ty;

  //  uint32_t floor_color = ft_pixel(100, 100, 100, 255);

	texture = mlx_load_png("./assets/textures/nasa_space.png");
	if (!texture)
	{
		printf("no texture?\n");
	}
	game->ceiling_ray = malloc(sizeof(t_ceiling_ray));
	if (!game->ceiling_ray)
		printf("error in game->ceiling_ray\n");
    y = 0;
	while (y < HEIGHT / 2)
	{
        //printf("x: %d, y: %d\n", x, y);
		// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		// X0 and Y0 represent the two farthest left edges and X1 and Y1 are
		// the two farthest right edges 
		game->ceiling_ray->dir_x0 = game->player->dir_x - game->player->plane_x;
		game->ceiling_ray->dir_y0 = game->player->dir_y - game->player->plane_y;
		game->ceiling_ray->dir_x1 = game->player->dir_x + game->player->plane_x;
		game->ceiling_ray->dir_y1 = game->player->dir_y + game->player->plane_y;

		// Current y position compared to the center of the screen (the horizon)
		// middle_line calculates the distance from the current Y row to the 'horizon' line,
		// which is the line in the middle of the screen (from top to bottom)
		// if greater then HEIGHT / 2, it is a row below the 'horizon'.
		// if smaller than HEIGHT / 2, it is a row above the 'horizon'.
		// if middle_line == 0, it is the 'horizon' line itself
		middle_line = y - HEIGHT / 2;

		// Vertical position of the camera.
		// the height I'm looking from, like the camera's height, not the player's
		game->ceiling_ray->pos_z = 0.5 * HEIGHT;
		// Horizontal distance from the camera to the floor for the current row.
		// 0.5 is the z position exactly in the middle between floor and ceiling.
        if (middle_line != 0)
        {
			// this is the value that will be used to work like the image effect in 
			// which an image is stretched to seem smaller or bigger
			// at the bottom or at the top
			// this value will depend on the calculation of pos_z and middle_line to find
			// which rows are closer to the middle line and to stretch its pixels to look as
			// if they're far away. And if the rows are further, to not stretch it as much, so they appear smaller
		    game->ceiling_ray->row_distance = game->ceiling_ray->pos_z / middle_line;

		    // calculate the real world step vector we have to add for each x (parallel to camera plane)
		    // adding step by step avoids multiplications with a weight in the inner loop
		    game->ceiling_ray->floor_step_x = game->ceiling_ray->row_distance
		    	* (game->ceiling_ray->dir_x1 - game->ceiling_ray->dir_x0) / WIDTH;
		    game->ceiling_ray->floor_step_y = game->ceiling_ray->row_distance
		    	* (game->ceiling_ray->dir_y1 - game->ceiling_ray->dir_y0) / WIDTH;

				
		    // real world coordinates of the leftmost column. This will be updated as we step to the right.
		    game->ceiling_ray->floor_x = game->player->pos_x
		    	+ game->ceiling_ray->row_distance * game->ceiling_ray->dir_x0;
		    game->ceiling_ray->floor_y = game->player->pos_y
		    	+ game->ceiling_ray->row_distance * game->ceiling_ray->dir_y0;
		    x = 0;
		    while (x < WIDTH)
		    {
                //printf("x: %d, y: %d\n", x, y);
                printf("WIDTH: %d, texture->width: %d\n", WIDTH, texture->width);
		    	// the cell coord is simply got from the integer parts of floorX and floorY
		    	game->ceiling_ray->cell_x = (int)(game->ceiling_ray->floor_x);
		    	game->ceiling_ray->cell_y = (int)(game->ceiling_ray->floor_y);
		    	// get the texture coordinate from the fractional part
                tx = (int)(texture->width * (game->ceiling_ray->floor_x
					- game->ceiling_ray->cell_x)) & (texture->width - 1);
		    	ty = (int)(texture->height * (game->ceiling_ray->floor_y
		    				- game->ceiling_ray->cell_y)) & (texture->height - 1);
                printf("x: %d, tx: %d\n", x, tx);
                //printf("tx: %d, ty: %d, floor_x: %f, floor_y: %f\n", tx, ty, game->ceiling_ray->floor_x, game->ceiling_ray->floor_y);
		    	game->ceiling_ray->floor_x += game->ceiling_ray->floor_step_x;
		    	game->ceiling_ray->floor_y += game->ceiling_ray->floor_step_y;
		    	// draw floor
		    	draw_ceiling(game, texture, tx, ty, y);
		    	// draw ceiling (symmetrical, at screenHeight - y - 1 instead of y)
		    	//draw_floor_ceiling(game, texture, tx, ty, HEIGHT - y - 1);
		    	x++;
		    }
        }
		y++;
	}
        // Draw the floor color
//    for (y = HEIGHT / 2; y < HEIGHT; y++)
//    {
//        for (x = 0; x < WIDTH; x++)
//            mlx_put_pixel(game->img, x, y, floor_color);
//    }
	mlx_delete_texture(texture);
	free(game->ceiling_ray);
}

// void	draw_ceiling_and_floor(t_game *game)
//{
//	int				i;
//	int				j;
//	unsigned int	ceiling;
//	unsigned int	floor;
//
//	i = 0;
//	j = 0;
//	ceiling = game->map->ceiling;
//	floor = game->map->floor;
//	while (i < WIDTH)
//	{
//		j = 0;
//		while (j < HEIGHT)
//		{
//			if (j < HEIGHT / 2)
//				mlx_put_pixel(game->img, i, j, ceiling);
//			else
//				mlx_put_pixel(game->img, i, j, floor);
//			j++;
//		}
//		i++;
//	}
//}
