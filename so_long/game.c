/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:47:25 by rkorhone          #+#    #+#             */
/*   Updated: 2024/04/24 17:47:29 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "const.h"
#include "data.h"
#include "game.h"
#include "game_events.h"
#include "entity.h"
#include "render.h"
#include "resources.h"
#include "flood_fill.h"
#include "MLX42/include/MLX42/MLX42.h"
#include "libft/libft.h"

// gets the first entity at same position as entity unit
// returns the entity or NULL
static t_ent	*ent_at(t_runtime *rd, t_ent *unit)
{
	t_list	*cur;
	t_ent	*ent;

	cur = *(rd->ent_list);
	while (cur != NULL)
	{
		ent = (t_ent *)cur->data;
		if (ent->x == unit->x && ent->y == unit->y)
		{
			if (ent->enabled && ent != unit && ent->type != Floor)
				return (ent);
		}
		cur = cur->next;
	}
	return (NULL);
}

// checks for collisions of entities for entity 'unit'
static void	collision_check(t_runtime	*rd, t_ent *unit)
{
	t_ent		*ent;

	ent = ent_at(rd, unit);
	if (ent != NULL)
	{
		if (ent->type == Point)
			collect_point(rd, ent);
		else if (ent->type == Exit)
			mlx_close_window(rd->mlx);
	}
}

// try move entity unit to dir x and dir y
// performs collision check and updates sprite positon on success
// returns 1 on succesfull movement and 0 on fail
static int	move(t_runtime *rd, t_ent *unit, int x_dir, int y_dir)
{
	int	x;
	int	y;

	x = unit->x + x_dir;
	y = unit->y + y_dir;
	if (x < 0 || y < 0 || x >= rd->map->width || y >= rd->map->height)
		return (0);
	if (rd->map->nodes[y][x].type != Wall)
	{
		if (unit == rd->player_ent)
		{
			rd->moves++;
			ft_printf("moves: %d\n", rd->moves);
		}
		unit->x += x_dir;
		unit->y += y_dir;
		update_ent_position(rd, unit);
		collision_check(rd, unit);
		return (1);
	}
	return (0);
}

// mlx hook to handle player inputs
// only registers key down inputs when all keys are up
static void	input(void *param)
{
	t_runtime	*rd;

	rd = param;
	if (mlx_is_key_down(rd->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(rd->mlx);
	if (mlx_is_key_down(rd->mlx, MLX_KEY_UP) && !rd->key_down)
		rd->key_down = move(rd, rd->player_ent, 0, -1);
	else if (mlx_is_key_down(rd->mlx, MLX_KEY_DOWN) && !rd->key_down)
		rd->key_down = move(rd, rd->player_ent, 0, 1);
	else if (mlx_is_key_down(rd->mlx, MLX_KEY_RIGHT) && !rd->key_down)
		rd->key_down = move(rd, rd->player_ent, 1, 0);
	else if (mlx_is_key_down(rd->mlx, MLX_KEY_LEFT) && !rd->key_down)
		rd->key_down = move(rd, rd->player_ent, -1, 0);
	if (mlx_is_key_down(rd->mlx, MLX_KEY_UP)
		|| mlx_is_key_down(rd->mlx, MLX_KEY_DOWN)
		|| mlx_is_key_down(rd->mlx, MLX_KEY_RIGHT)
		|| mlx_is_key_down(rd->mlx, MLX_KEY_LEFT))
		rd->key_down = 1;
	else
		rd->key_down = 0;
}

// main logic, validates that everything works before running
// and free everything after
void	start_game(t_map *map, int width, int height)
{
	t_runtime	rd;

	rd = (t_runtime){0};
	rd.map = map;
	rd.width = width;
	rd.height = height;
	rd.scale = 1;
	rd.mlx = mlx_init(map->width * GRID, map->height * GRID, "So Long", false);
	if (rd.mlx != NULL)
	{
		load_resources(&rd);
		if (create_entities(&rd, map))
		{
			disable_ent(rd.exit_ent);
			if (flood_fill_check(&rd) && validate_resources(&rd))
			{
				mlx_loop_hook(rd.mlx, input, &rd);
				mlx_loop(rd.mlx);
			}
		}
		free_resources(&rd);
		mlx_terminate(rd.mlx);
		list_delete(rd.ent_list, 1);
	}
}
