/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:47:25 by rkorhone          #+#    #+#             */
/*   Updated: 2024/04/24 17:47:29 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "data.h"
#include "list.h"
#include "flood_fill.h"
#include "libft/libft.h"
#include <stdlib.h>

// get valid map node at x y coords
// return NULL if our of bounds
static t_map_node	*get_node(t_map *map, int x, int y)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (NULL);
	return (&map->nodes[y][x]);
}

// checks adjacent map nodes from cur
static void	check_adjacent(t_list **visited, t_map *map, t_map_node *cur)
{
	t_map_node	*node;
	int			i;
	const int	dir_x[4] = {1, -1, 0, 0};
	const int	dir_y[4] = {0, 0, 1, -1};

	i = 0;
	while (i < 4)
	{
		node = get_node(map, cur->x + dir_x[i], cur->y + dir_y[i]);
		if (node != NULL && node->type != Wall && !list_find(visited, node))
		{
			if (list_add(visited, node))
				check_adjacent(visited, map, node);
		}
		i++;
	}
}

// count all reachable objects (points and exists) in flood filled map nodes
static	int	count_reachable(t_list **visited)
{
	int			objectives;
	t_list		*cur;
	t_map_node	node;

	objectives = 0;
	if (visited == NULL)
		return (0);
	cur = *visited;
	while (cur != NULL)
	{
		node = *((t_map_node *)cur->data);
		if (node.type == Point || node.type == Exit)
			objectives++;
		cur = cur->next;
	}
	return (objectives);
}

// flood fill each map node from player position
// return 1 if all objectives (score + exit) are reachable
// return 0 on malloc fail or if all objectives cant be reached
int	flood_fill_check(t_runtime *rd)
{
	t_list		**visited;
	t_map_node	node;
	int			reachable;

	visited = list_create();
	if (visited == NULL)
		return (0);
	if (rd->player_ent == NULL)
		return (0);
	node = rd->map->nodes[rd->player_ent->y][rd->player_ent->x];
	if (list_add(visited, &node))
		check_adjacent(visited, rd->map, &node);
	reachable = count_reachable(visited);
	list_delete(visited, 0);
	if (reachable == rd->map->objects[Point] + 1)
		return (1);
	error_msg(-7);
	return (0);
}
