/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:47:25 by rkorhone          #+#    #+#             */
/*   Updated: 2024/04/24 17:47:29 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "data.h"
#include "map_parser.h"
#include "list.h"
#include "libft/libft.h"
#include <fcntl.h>
#include <unistd.h>

// coverts a char to int (enum)
int	char_to_enum(char c)
{
	if (c == '0')
		return ((int)Floor);
	else if (c == '1')
		return ((int)Wall);
	else if (c == 'P')
		return ((int)Player);
	else if (c == 'C')
		return ((int)Point);
	else if (c == 'E')
		return ((int)Exit);
	return ((int)Error);
}

// counts all types in a row
static void	parse_line(t_map *md, char *line)
{
	int	width;

	width = 0;
	while (*line != 0)
	{
		if (*line == '\n')
			break ;
		md->objects[char_to_enum(*line)]++;
		line++;
		width++;
	}
	if (width != md->width)
		md->objects[Error]++;
}

// reads the mapfile and returns a list of read strings
t_list	**read_map(t_map *md, char *filename)
{
	t_list	**list;
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	list = list_create();
	if (list == NULL)
		return (NULL);
	line = get_next_line(fd);
	md->width = ft_strlen(line) - 1;
	if (line != NULL)
	{
		while (line != NULL)
		{
			list_add(list, line);
			md->height++;
			parse_line(md, line);
			line = get_next_line(fd);
		}
	}
	close (fd);
	return (list);
}

// makes sure all map bounds are walls
// returns 0 if not or 1 if they are
static int	check_borders(t_map *md)
{
	int	x;
	int	y;

	if (md->nodes == NULL)
		return (0);
	y = 0;
	while (y < md->height)
	{
		x = 0;
		while (x < md->width)
		{
			if (y == 0 || y == md->height - 1
				|| x == 0 || x == md->width - 1)
			{
				if (md->nodes[y][x].type != Wall)
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

// validates map, TODO: return error code
int	validate_map(t_map *md)
{
	if (md != NULL)
		return (0);
	if (md->nodes == NULL)
		return (-6);
	if (check_borders(md) != 1)
		return (-1);
	if (md->objects[Player] != 1)
		return (-2);
	if (md->objects[Point] < 1)
		return (-3);
	if (md->objects[Exit] != 1)
		return (-4);
	if (md->objects[Error] > 0)
		return (-5);
	return (1);
}
