/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:47:25 by rkorhone          #+#    #+#             */
/*   Updated: 2024/04/24 17:47:29 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "data.h"
#include "map.h"
#include "game.h"
#include "render.h"
#include "resources.h"
#include "list.h"
#include "MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>

// creates a specific type entity at xy position
// returns NULL on malloc fail or pointer to entity on success
t_ent	*create_ent(t_runtime *rd, int x, int y, t_type type)
{
	t_ent	*ent;

	ent = malloc(sizeof(t_ent));
	if (ent == NULL)
		return (NULL);
	ent->x = x;
	ent->y = y;
	ent->mlx_id = -1;
	ent->sprite = rd->sprites[type];
	ent->type = type;
	ent->enabled = 1;
	if (!list_add(rd->ent_list, ent))
	{
		free(ent);
		return (NULL);
	}
	return (ent);
}

// populates specific map grid position with required entities
// (non floor entities always have floor under them)
// returns 0 on malloc fail or 1 on success
static int	create_map_ent(t_runtime *rd, int x, int y, t_type type)
{
	t_ent	*ent;

	if (type != Wall)
	{
		ent = create_ent(rd, x, y, Floor);
		if (ent == NULL)
			return (0);
		ent->mlx_id = render_ent(rd, ent, 0);
	}
	if (type != Floor)
	{
		ent = create_ent(rd, x, y, type);
		if (ent == NULL)
			return (0);
		if (ent->type == Player)
			rd->player_ent = ent;
		if (ent->type == Exit)
			rd->exit_ent = ent;
		ent->mlx_id = render_ent(rd, ent, 3);
	}
	return (1);
}

// create all entities in map grid
// returns 0 on malloc fail or 1 on success
int	create_entities(t_runtime *rd, t_map *map)
{
	int			x;
	int			y;

	rd->ent_list = list_create();
	if (rd->ent_list == NULL)
		return (0);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (!create_map_ent(rd, x, y, map->nodes[y][x].type))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

// enables specific entity rendering if it has a sprite and mlx id
void	enable_ent(t_ent *ent)
{
	if (ent == NULL)
		return ;
	if (ent->sprite != NULL && ent->mlx_id != -1)
		ent->sprite->instances[ent->mlx_id].enabled = true;
	ent->enabled = 1;
}

// disabled specific entity rendering if it has a sprite and mlx id
void	disable_ent(t_ent *ent)
{
	if (ent == NULL)
		return ;
	if (ent->sprite != NULL && ent->mlx_id != -1)
		ent->sprite->instances[ent->mlx_id].enabled = false;
	ent->enabled = 0;
}
