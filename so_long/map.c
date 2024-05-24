/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:47:25 by rkorhone          #+#    #+#             */
/*   Updated: 2024/04/24 17:47:29 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "const.h"
#include "data.h"
#include "map.h"
#include "list.h"
#include "map_parser.h"
#include "libft/libft.h"
#include <stdlib.h>

// limit map size to 32x32
static int	limit_map(t_map *map)
{
	if (map->width <= 32 && map->height <= 32)
		return (1);
	return (0);
}

// main map creation logic to initialize struct
// returns the map struct
t_map	*create_map(char *filename)
{
	t_map	*map;
	t_list	**list_str;

	map = malloc(sizeof(t_map));
	if (map == NULL)
		return (NULL);
	map->nodes = NULL;
	map->width = 1;
	map->height = 0;
	map->objects[Floor] = 0;
	map->objects[Wall] = 0;
	map->objects[Player] = 0;
	map->objects[Point] = 0;
	map->objects[Exit] = 0;
	map->objects[Error] = 0;
	list_str = NULL;
	list_str = read_map(map, filename);
	if (limit_map(map))
		build_map(map, list_str);
	list_delete(list_str, 1);
	return (map);
}

// builds the row y for 2d array
static void	build_row(t_map *md, int y, char *str)
{
	int	x;

	x = 0;
	while (x < md->width)
	{
		md->nodes[y][x].x = x;
		md->nodes[y][x].y = y;
		md->nodes[y][x].type = char_to_enum(*str);
		x++;
		str++;
	}
}

// mallocs 2d array for map nodes from list of strings
// returns -1 on malloc fail or 1 on success
int	build_map(t_map	*md, t_list **list_str)
{
	int		y;
	char	*str;
	t_list	*cur;

	if (*list_str == NULL)
		return (-1);
	md->nodes = malloc(sizeof(t_map_node *) * md->height);
	if (md->nodes == NULL)
		return (-1);
	y = 0;
	cur = *list_str;
	str = cur->data;
	while (y < md->height)
	{
		md->nodes[y] = malloc(sizeof(t_map_node) * md->width);
		if (md->nodes[y] == NULL)
			return (-1);
		build_row(md, y, str);
		cur = cur->next;
		if (cur != NULL)
			str = cur->data;
		y++;
	}
	return (1);
}

// frees all nodes in map
void	*free_map(t_map *md)
{
	int	y;

	if (md == NULL)
		return (NULL);
	if (md->nodes != NULL)
	{
		y = 0;
		while (y < md->height)
		{
			free(md->nodes[y]);
			y++;
		}
		free(md->nodes);
	}
	free(md);
	return (NULL);
}
