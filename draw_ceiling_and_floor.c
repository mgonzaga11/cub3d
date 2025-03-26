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

// Function to get the pixel color from a floor/ceiling texture
uint32_t get_current_pixel_color_floor_ceiling(mlx_texture_t *texture, int tex_x, int tex_y) {
    int pixel_index = (tex_y * texture->width + tex_x) * 4;
    uint8_t red = texture->pixels[pixel_index];
    uint8_t green = texture->pixels[pixel_index + 1];
    uint8_t blue = texture->pixels[pixel_index + 2];
    uint8_t alpha = texture->pixels[pixel_index + 3];
    return ft_pixel(red, green, blue, alpha); // Assuming you have a ft_pixel function
}

// Function to draw a floor or ceiling pixel
void draw_floor_ceiling(t_game *game, mlx_texture_t *texture, int tex_x, int tex_y, int screen_y) {
    uint32_t color = get_current_pixel_color_floor_ceiling(texture, tex_x, tex_y);
    if (screen_y >= 0 && screen_y < HEIGHT && tex_x >= 0 && tex_x < WIDTH) {
        mlx_put_pixel(game->img, tex_x, screen_y, color);
    }
}

void	draw_ceiling_and_floor(t_game *game)
{
	int		x;
	int		y;
	int		p;

	mlx_texture_t	*texture;

	texture = mlx_load_png("./assets/textures/ceiling_one.png");
	if (!texture)
	{
		printf("no texture?\n");
	}

	y = 0;
	game->ceiling_ray = malloc(sizeof(t_ceiling_ray));
	if (!game->ceiling_ray)
		printf("error in game->ceiling_ray\n");
    while(y < HEIGHT)
    {
      // rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
    	game->ceiling_ray->dir_x0 = game->player->dir_x - game->player->plane_x;
      	game->ceiling_ray->dir_y0 = game->player->dir_y - game->player->plane_y;
		game->ceiling_ray->dir_x1 = game->player->dir_x + game->player->plane_x;
		game->ceiling_ray->dir_y1= game->player->dir_y + game->player->plane_y;

      // Current y position compared to the center of the screen (the horizon)
      p = y - HEIGHT / 2;

      // Vertical position of the camera.
      game->ceiling_ray->pos_z = 0.5 * HEIGHT;

      // Horizontal distance from the camera to the floor for the current row.
      // 0.5 is the z position exactly in the middle between floor and ceiling.
      game->ceiling_ray->row_distance = game->ceiling_ray->pos_z / p;

      // calculate the real world step vector we have to add for each x (parallel to camera plane)
      // adding step by step avoids multiplications with a weight in the inner loop
      game->ceiling_ray->floor_step_x = game->ceiling_ray->row_distance * (game->ceiling_ray->dir_x1 - game->ceiling_ray->dir_x0) / WIDTH;
      game->ceiling_ray->floor_step_y = game->ceiling_ray->row_distance * (game->ceiling_ray->dir_y1 - game->ceiling_ray->dir_y0) / WIDTH;

      // real world coordinates of the leftmost column. This will be updated as we step to the right.
      game->ceiling_ray->floor_x = game->player->pos_x + game->ceiling_ray->row_distance * game->ceiling_ray->dir_x0;
      game->ceiling_ray->floor_y = game->player->pos_y + game->ceiling_ray->row_distance * game->ceiling_ray->dir_y0;
	
	  x = 0;
      while(x < WIDTH)
      {
        // the cell coord is simply got from the integer parts of floorX and floorY
        game->ceiling_ray->cell_x = (int)(game->ceiling_ray->floor_x);
        game->ceiling_ray->cell_y = (int)(game->ceiling_ray->floor_y);

        // get the texture coordinate from the fractional part
        int tx = (int)(texture->width * (game->ceiling_ray->floor_x - game->ceiling_ray->cell_x)) & (texture->width - 1);
        int ty = (int)(texture->height * (game->ceiling_ray->floor_y - game->ceiling_ray->cell_y)) & (texture->height - 1);

        game->ceiling_ray->floor_x += game->ceiling_ray->floor_step_x;
        game->ceiling_ray->floor_y += game->ceiling_ray->floor_step_y;

        // draw floor
		draw_floor_ceiling(game, texture, tx, ty, y);

		// draw ceiling (symmetrical, at screenHeight - y - 1 instead of y)
		draw_floor_ceiling(game, texture, tx, ty, HEIGHT - y - 1);
		x++;
      }
	  y++;
    }
	mlx_delete_texture(texture);
    free(game->ceiling_ray);
}

//void	draw_ceiling_and_floor(t_game *game)
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

