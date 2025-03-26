# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/25 18:38:48 by mgonzaga          #+#    #+#              #
#    Updated: 2025/03/24 18:43:38 by mgonzaga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME := cub3D

CC := cc

C_FLAGS := -g3 -Wall -Wextra -Werror

MLX_FLAGS = -lm -ldl -pthread -lglfw

LIBFT_DIR := ./libft

LIBFT := libft/libft.a

MLXLIB := MLX42/build/libmlx42.a

FILES := main.c 01_init_game.c 02_init_structs.c init_player_struct.c init_mlx.c\
		calculate_rays.c wall_calculations.c wall_colours.c key_hooks.c key_hooks_2.c \
		parsing/character_mapvalidation.c parsing/check_argv.c parsing/map_validation.c \
		parsing/parsing_content.c parsing/player_mapvalidation.c parsing/read_argv.c \
		parsing/utils.c parsing/wall_mapvalidation.c get_content/get_info_map.c \
		get_content/get_info_utils.c get_content/get_info.c draw_ceiling_and_floor.c


OBJ := $(FILES:.c=.o)

all: $(MLXLIB) $(LIBFT) $(NAME)

%.o: %.c 
	$(CC) $(C_FLAGS) -c $< -o $@

$(LIBFT): 
	@make -C $(LIBFT_DIR) > /dev/null 2>&1
	@echo "Compiling libft..."

$(MLXLIB):
	@cmake -S MLX42 -B MLX42/build > /dev/null 2>&1
	@make -j4 -C MLX42/build > /dev/null 2>&1
	@echo "Compiling mlx42..."

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(C_FLAGS) $(OBJ) $(MLXLIB) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "Compiling cub3D..."
	@$(MAKE) -s print_message

clean: 
	@rm -f $(OBJ) > /dev/null 2>&1
	@make -C $(LIBFT_DIR) clean > /dev/null 2>&1
	@echo "Cleaning cub3D object files..."
	@echo "Cleaning libft object files..."

fclean: clean
	@rm -f $(NAME) > /dev/null 2>&1
	@make -C $(LIBFT_DIR) fclean  > /dev/null 2>&1
	@rm -rf MLX42/build > /dev/null 2>&1
	@echo "Cleaning cub3D..."
	@echo "Cleaning libft directory..."
	@echo "Cleaning mlx42/build directory..."

print_message:
	@echo "----------------------------------------"
	@echo "|                                      |"
	@echo "|       Program Fully Compiled!        |"
	@echo "|                                      |"
	@echo "----------------------------------------"

v: all
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

re: fclean all

.PHONY: all fclean clean re v print_message
