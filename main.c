/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:21:32 by mgonzaga          #+#    #+#             */
/*   Updated: 2025/01/29 18:52:10 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

int	print_error(char *e)
{
	printf("Error\n%s", e);
	return (1);
}

int check_name(char *argv)
{
	int count;
	count = ft_strlen(argv);
	if (ft_strncmp(&argv[count - 4], ".cub", 4) == 0)
		return (0);
	return (1);
}

int check_arguments(int argc, char *argv)
{

	if(argc == 1)
	{
		write(1, "Error: Not enough params!", 24);
		return(1);
	}
	else if(argc > 2)
	{
		write(1, "Error: Too many params!", 23);
		return(1);
	}
	else if(check_name(argv) == 1)
	{
		write(1, "Error: The file need be .cub\n", 32);
		return(1);
	}
	return(0);
}
int ampy_file(char *argv)
{
	int fd;
	char *string;
	
	fd = open(argv, O_RDONLY);
	string = get_next_line(fd);
	if(string == NULL)
		return(print_error(ERROR_2));

	return(0);
}



int main(int argc, char **argv)
{
	if(check_arguments(argc, argv[1]) == 1)
		return(1);
	if(ampy_file(argv[1]) == 1)
		return(1);
	if(read_content(argv[1]) == 1)
		return(1);
	mlx_t* mlx = mlx_init(1024, 1024, "Cub3D", true);
	mlx_loop(mlx);	
	return(0);
}

