/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:44:46 by mgonzaga          #+#    #+#             */
/*   Updated: 2025/03/26 13:46:24 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_3D_H
# define CUB_3D_H

# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include <math.h>
# define ERROR_1 "Impossible to read the file\n"
# define ERROR_2 "Empty File\n"
# define ERROR_3 "Invalid malloc\n"
# define ERROR_4 "Not enough params!\n"
# define ERROR_5 "Too many params!\n"
# define ERROR_6 "The file need be .cub\n"
# define ERROR_7 "Invalid Numbers Elements\n"
# define ERROR_8 "Invalid Elements\n"
# define ERROR_9 "Wrong color number\n"
# define ERROR_10 "Invalid taxture\n"
# define ERROR_11 "Invalid player in map\n"
# define ERROR_12 "Invalid Character in map\n"
# define ERROR_13 "Invalid Wall in map\n"
# define ERROR_14 "Empty line in map\n"
# define ERROR_15 "Failed to open PNG file\n"
# define ERROR_16 "Impossible to init game\n"
# define ERROR_17 "Failed to open MLX window\n"
# define ERROR_18 "Failed to init MLX image\n"

# define WIDTH 800
# define HEIGHT 800
# define MOVE_SPEED 0.1
# define ROTATION_SPEED 0.1

typedef struct s_position
{
	char	direction;
	int 	x;
	int		y;
} 	t_position;

typedef struct s_content
{
	char		**map;
	char		*NO_path;
	char		*SO_path;
	char		*WE_path;
	char		*EA_path;
	char		**color_C;
	char		**color_F;
	uint32_t	ceiling;
	uint32_t	floor;
	int			map_max_x; // value to store height size
	int			map_max_y; // value to store width size
}			t_content;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}			t_player;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		hit;
}			t_ray;

typedef struct s_ceiling_ray
{
	float	dir_x0;
	float	dir_y0;
    float	dir_x1;
    float	dir_y1;
	float	pos_z;
	float	row_distance;
	float	floor_step_x;
	float	floor_step_y;
	float	floor_x;
	float	floor_y;
	int		cell_x;
	int		cell_y;
	int		tx;
	int		ty;
	int		floor_texture;
	int		ceiling_texture;
}			t_ceiling_ray;

typedef struct s_textures
{
	mlx_texture_t	*NO_path;
	mlx_texture_t	*SO_path;
	mlx_texture_t	*WE_path;
	mlx_texture_t	*EA_path;
	double			wall_x;
	double			step;
	double			tex_pos;
	int				tex_x;
	int				tex_y;
}	t_textures;

typedef struct s_game
{
	t_ray		*ray;
	t_player	*player;
	t_content	*map;
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_textures	*textures;
	t_ceiling_ray *ceiling_ray;
}	t_game;

//#Parsing//

//character_mapvalidation
int	invalid_character(char **file_matrix);
int	validate_char(char *string);

//check_argv
int	check_arguments(int argc, char *argv);
int	check_name(char *argv);
int	empty_file(char *argv);

//map_validation
int	validation_map(char **file_matrix);
int	validate_content(char **matrix_file);

//parsing_content
int	check_elements(char **matrix);
int	validate_element(char *matrix_line, int line_number);
int	validate_numbers(char **matrix);
int	check_numbers(char *string, int count);
int	texture_path(char **m);

//player_mapvalidation
int	only_player(char *string);
int	find_player(char **file_matrix);

//read_argv
int		countcols(char *file_name);
char	**makematrix(char *file_name, int count_cols);
int		find_map(char **file_matrix);

//utils
int		print_error(char *error);
int		walk_spaces(char *string);
void	free_matrix(char **malloc_string);

//wall_mapvalidation
int	validate_wall(char **file_matrix);
int	check_wall(char **matrix, int cols, int i);
int	empty_line(char **file_matrix);


//#get_content

//get_info_map
int	get_map(char **file_matrix, t_content *s_content);
int	get_map_sizes_y(char **file_matrix);
int	get_map_sizes_x(char **file_matrix);
char *get_map_string(int size_x, char *string);

//get_info_utils
int	get_texture_path(char **matrix, t_content *s_content);
char	*get_string(char *string, int count);
uint32_t	ft_pixel(uint32_t r, uint32_t g, uint32_t b, uint32_t a);
void	get_color_number(t_content *s_content);

//get_info
int		get_content(char **file_matrix, t_content *s_content);
int		get_color(char **matrix, t_content *s_content);
char	**get_color_split(char *string, int count);

// init_game
int		init_game(t_game *game);
void		render_raycast_frame(void *param);
void		draw_walls_with_texture(int x, t_game *game);

// init_mlx
int				init_window(t_game *game);
mlx_image_t		*init_img(t_game *game);
t_textures		*init_textures(t_game *game);
mlx_texture_t	*get_wall_texture(t_game *game);

// init_structs
int	init_structs_in_game(t_game *game);
void	draw_ceiling_and_floor(t_game *game);
int	get_rgba(int r, int g, int b, int a);

// init player_struct
t_player	*init_player_struct(t_content *map);
t_content		*init_map_struct(void);

// player movements
void	move_player_w(t_game *game);
void	move_player_s(t_game *game);
void	move_player_a(t_game *game);
void	move_player_d(t_game *game);
void	move_player_vision_left(t_game *game);
void	move_player_vision_right(t_game *game);

// calculate_rays
void	init_ray_pos_and_dir(int x, t_ray *ray, t_player *player);
void	init_delta_distance(t_ray *ray);
void	init_step_and_sidedist(t_ray *ray, t_player *player);
void	perform_dda(t_ray *ray, t_content *map);
void	calculate_rays(int x, t_game *game);
int		find_map(char **file_matrix);
void 	get_color_number(t_content *s_content);

// wall_calculations.c
void	calculate_and_draw_walls(t_game *game, mlx_texture_t *texture, int x);
void	calculate_texture_step_and_position(t_game *game, int tex_height);
void	calculate_x_for_vertical_slice(t_game *game, int tex_width);
void	find_x_pixel(t_game *game);
void	get_wall_height(t_ray *ray);

// wall_colors.c
uint32_t	get_current_pixel_color(t_game *game, mlx_texture_t *texture);
int		get_pixel_index(t_game *game, mlx_texture_t *texture);

// key_hooks.c
void	key_pressed_function(mlx_key_data_t keydata, void *param);

void	draw_ceiling_and_floor(t_game *game);

#endif