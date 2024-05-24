/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:47:25 by rkorhone          #+#    #+#             */
/*   Updated: 2024/04/24 17:47:29 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "game.h"
#include "const.h"
#include "map.h"
#include "map_parser.h"
#include "libft/libft.h"

// checks that string str ends with ext
// returns 0 if its not found, 
// 0 if str or ext is NULL or 1 if found at the end of the string
static int	str_extension(char *str, char *ext)
{
	int	i;

	if (str == NULL || ext == NULL)
		return (0);
	while (*str != 0)
	{
		i = 0;
		while (ext[i] != 0 && str[i] != 0)
		{
			if (ext[i] != str[i])
				break ;
			i++;
		}
		if (ext[i] == 0 && str[i] == 0)
			return (1);
		str++;
	}
	return (0);
}

// prints out the specific error messages
void	error_msg(int error_code)
{
	ft_printf("Error Code %d: ", error_code);
	if (error_code == 0)
		ft_printf("Invalid map file\n");
	else if (error_code == -1)
		ft_printf("Borders are not walls\n");
	else if (error_code == -2)
		ft_printf("Number of P entites not equal to 1\n");
	else if (error_code == -3)
		ft_printf("Number of C entities is 0\n");
	else if (error_code == -4)
		ft_printf("Number of E entites not equal to 1\n");
	else if (error_code == -5)
		ft_printf("Invalid or out of bounds entity\n");
	else if (error_code == -6)
		ft_printf("Invalid map size (min 3 playable tiles, max 64x64)\n");
	else if (error_code == -7)
		ft_printf("Flood fill failed\n");
	else if (error_code == -8)
		ft_printf("Missing resources\n");
}

int	main(int argc, char **argv)
{
	t_map	*map;
	int		flag;

	map = NULL;
	if (argc > 1)
	{
		if (str_extension(argv[1], ".ber"))
			map = create_map(argv[1]);
		flag = validate_map(map);
		if (flag > 0)
			start_game(map, WIDTH, HEIGHT);
		else
			error_msg(flag);
	}
	else
		ft_printf("Error\nRun program with a map:\n./app \"maps/map.ber\"\n");
	free_map(map);
	return (0);
}
